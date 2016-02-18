/* gzlib.c -- zlib functions common to reading and writing gzip files
 * Copyright (C) 2004, 2010, 2011, 2012, 2013 Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

#include "gzguts.h"

#if defined(_WIN32) && !defined(__BORLANDC__)
#  define LSEEK _lseeki64
#else
#if defined(_LARGEFILE64_SOURCE) && _LFS64_LARGEFILE-0
#  define LSEEK lseek64
#else
#  define LSEEK lseek
#endif
#endif

/* Local functions */
local void gz_reset OF((gz_statep));
local gzFile gz_open OF((const void *, int, const char *));

#if defined(_WIN32)
char ZLIB_INTERNAL *gz_strerror(uInt error)
{
    char *buffer = NULL; errno_t err = 0;
    buffer = (char *)malloc(1024);  /* 1k is fine */
    if (buffer != NULL) {
        err = strerror_s(buffer, 1024, error);
        if (err != 0) { free(buffer); buffer = NULL; }
    }
    return buffer;
}
#endif  /* _WIN32 */

#if defined(UNDER_CE)
/* 
 * Map the Windows error number in ERROR to a locale-dependent error 
 * message string and return a pointer to it.  Typically, the values 
 * for ERROR come from GetLastError.

 * The string pointed to shall not be modified by the application, but 
 * may be overwritten by a subsequent call to gz_strwinerror

 * The gz_strwinerror function does not change the current setting of
 * GetLastError. 
 * 
 * Anyways, this function is not suitable for multi-thread
 */
char ZLIB_INTERNAL *gz_strwinerror(uInt error)
{
    char *buffer = NULL; char *tempbuf = NULL;
    DWORD chars = 0; int cchars = 0; DWORD lasterr = 0; 
    lasterr = GetLastError();       /* svae current error code */
    chars = FormatMessageA (
        FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER, 
        NULL, (DWORD)error, 0, (LPTSTR)&tempbuf, (DWORD)0, NULL 
    ); 
    if (chars != 0 && tempbuf != NULL) {
        /* If there is an \r\n appended, zap it. */
        if (chars >= 2 && 
            tempbuf[chars-2] == '\r' && tempbuf[chars-1] == '\n') {
            chars -= 2; tempbuf[chars-2] = 0; tempbuf[chars-1] = 0;
        }
        buffer = (char *)malloc(chars + 1);
        if (buffer != NULL) { strcpy_s(buffer, chars+1, tempbuf); }
        /* 
         * LocalFree is not in the modern SDK (on Windows 10), 
         * so it cannot be used to free the result buffer.
         * Instead, use HeapFree (GetProcessHeap(), allocatedMessage). 
         * In this case, this is the same as calling LocalFree on 
         * memory.
         */
        LocalFree(tempbuf);         /* free the buffer */
    } else {
        buffer = (char *)malloc(1024);
        if (buffer != NULL) {
            cchars = _snprintf_s(buffer, 1024, 
                _TRUNCATE, "unknown win32 error (%ld)", error);
            if(cchars <= 0) { free(buffer); buffer = NULL; }
        }
    }
    SetLastError(lasterr);          /* recover the last error */
    return (char ZLIB_INTERNAL *)buffer;
}
#endif  /* UNDER_CE */


/* Reset gzip file state */
local void gz_reset(state)
    gz_statep state;
{
    state->x.have = 0;              /* no output data available */
    if (state->mode == GZ_READ) {   /* for reading ... */
        state->eof = 0;             /* not at end of file */
        state->past = 0;            /* have not read past end yet */
        state->how = LOOK;          /* look for gzip header */
    }
    state->seek = 0;                /* no seek request pending */
    gz_error(state, Z_OK, NULL);    /* clear error */
    state->x.pos = 0;               /* no uncompressed data yet */
    state->strm.avail_in = 0;       /* no input data yet */
}


/* Open a gzip file either by name or file descriptor. */
local gzFile gz_open(path, fd, mode)
    const void *path;
    int fd;
    const char *mode;
{
    gz_statep state = NULL; size_t len = 0; int oflag = 0;
    
#ifdef _WIN32
    errno_t err = 0;
#endif

#ifdef O_CLOEXEC
    int cloexec = 0;
#endif
#ifdef O_EXCL
    int exclusive = 0;
#endif

    /* check input */
    if (path == NULL) return NULL;

    /* allocate gzFile structure to return */
    state = (gz_statep)malloc(sizeof(gz_state));
    if (state == NULL) return NULL;
    state->msg = NULL;                  /* no error message yet */
    state->want = GZBUFSIZE;            /* requested buffer size */
    state->size = 0;                    /* no buffers allocated yet */
 
    /* interpret mode */
    state->mode = GZ_NONE;
    state->level = Z_DEFAULT_COMPRESSION;
    state->direct = 0;
    state->strategy = Z_DEFAULT_STRATEGY;
    while (*mode) {
        if (*mode >= '0' && *mode <= '9')
            state->level = *mode - '0';
        else
            switch (*mode) {
            case 'r':
                state->mode = GZ_READ;
                break;
#ifndef NO_GZCOMPRESS
            case 'w':
                state->mode = GZ_WRITE;
                break;
            case 'a':
                state->mode = GZ_APPEND;
                break;
#endif
            case '+':       /* can't read and write at the same time */
                free(state);
                return NULL;
            case 'b':       /* ignore -- will request binary anyway */
                break;
#ifdef O_CLOEXEC
            case 'e':
                cloexec = 1;
                break;
#endif
#ifdef O_EXCL
            case 'x':
                exclusive = 1;
                break;
#endif
            case 'f':
                state->strategy = Z_FILTERED;
                break;
            case 'h':
                state->strategy = Z_HUFFMAN_ONLY;
                break;
            case 'R':
                state->strategy = Z_RLE;
                break;
            case 'F':
                state->strategy = Z_FIXED;
                break;
            case 'T':
                state->direct = 1;
                break;
            default:    /* could consider as an error, but just ignore */
                ;
            }
        mode++;
    }

    /* must provide an "r", "w", or "a" */
    if (state->mode == GZ_NONE) { free(state); return NULL; }

    /* can't force transparent read */
    if (state->mode == GZ_READ) {
        if (state->direct) { free(state); return NULL; }
        state->direct = 1;          /* for empty file */
    }

    /* save the path name for error messages */
#ifdef _WIN32
    if (fd == -2) {
        /* Here, use security version instead. */
        err = wcstombs_s(&len, NULL, 0, path, 0);
        if (err != 0) { free(state); return NULL; }
    } else
#endif
    { len = strlen((const char *)path); }
    state->path = (char *)malloc(len + 1);
    if (state->path == NULL) { free(state); return NULL; }
#ifdef _WIN32
    if (fd == -2) {
        if (len) {
            err = wcstombs_s(
                &len, state->path, len+1, path, _TRUNCATE);
            if (err != 0) {
                free(state->path); free(state); return NULL;
            }
        } else *(state->path) = 0;
    } else
#endif
    /* Here use the security version instead */
    { strncpy_s(state->path, len+1, path, len); }

    /* compute the flags for open() */
    oflag =
#ifdef O_LARGEFILE
        O_LARGEFILE |
#endif
#ifdef O_BINARY
        O_BINARY |
#endif
#ifdef O_CLOEXEC
        (cloexec ? O_CLOEXEC : 0) |
#endif
        (state->mode == GZ_READ ? O_RDONLY : (O_WRONLY | O_CREAT |
#ifdef O_EXCL
            (exclusive ? O_EXCL : 0) |
#endif
            (state->mode == GZ_WRITE ? O_TRUNC : O_APPEND))
        );

    /* open the file with the appropriate flags (or just use fd) */
#ifdef _WIN32
    if (fd == -1) {
        printf("\nfile -> %d\n", state->fd);
        err = _sopen_s(
            &state->fd, path, oflag, _SH_DENYWR, _S_IREAD|_S_IWRITE);
    } else if (fd == -2) {
        err = _wsopen_s(
            &state->fd, path, oflag, _SH_DENYWR, _S_IREAD|_S_IWRITE);
    } else if (fd >= 0) {
        err = 0; state->fd = fd;
    } else {
        err = EINVAL; state->fd = -1;
    }
    if (err != 0) { free(state->path); free(state); return NULL; }
#else
    state->fd = fd > -1 ? fd : open((const char*)path, oflag, 0666);
    if (state->fd == -1) {
        free(state->path); free(state); return NULL;
    }
#endif

    if (state->mode == GZ_APPEND) state->mode = GZ_WRITE;

    /* save the current position for rewinding (only if reading) */
    if (state->mode == GZ_READ) {
        state->start = LSEEK(state->fd, 0, SEEK_CUR);
        if (state->start == -1) state->start = 0;
    }

    /* initialize stream */
    gz_reset(state);

    /* return stream */
    return (gzFile)state;
}

/* -- see zlib.h -- */
gzFile ZEXPORT gzopen(path, mode)
    const char *path;
    const char *mode;
{
    return gz_open(path, -1, mode);
}

/* -- see zlib.h -- */
gzFile ZEXPORT gzopen64(path, mode)
    const char *path;
    const char *mode;
{
    return gz_open(path, -1, mode);
}

/* -- see zlib.h -- */
gzFile ZEXPORT gzdopen(int fd, const char *mode)
{
    /* identifier for error messages */
    char *path; gzFile gz; int length = 0;

    if (fd < 0 || (path=(char *)malloc(7+3*sizeof(int))) == NULL)
        return NULL;

    /* Here, we simplify the code, snprintf must exist */
#if defined(_WIN32)
    length = _snprintf_s(                   /* for debugging */
        path, 7+3*sizeof(int), _TRUNCATE, "<fd:%d>", fd);  
    if (length <= 0 || length >= 7+3*sizeof(int)) {}
#else
    length = snprintf(                      /* for debugging */
        path, 7+3*sizeof(int), "<fd:%d>", fd); 
    if (length <= 0 || length >= 7+3*sizeof(int))
        path[7+3*sizeof(int)-1] = '\0';
#endif

    gz = gz_open(path, fd, mode); free(path); return gz;
}

/* -- see zlib.h -- */
#ifdef _WIN32
gzFile ZEXPORT gzopen_w(path, mode)
    const wchar_t *path;
    const char *mode;
{
    return gz_open(path, -2, mode);
}
#endif

/* -- see zlib.h -- */
int ZEXPORT gzbuffer(file, size)
    gzFile file;
    unsigned size;
{
    gz_statep state;

    /* get internal structure and check integrity */
    if (file == NULL)
        return -1;
    state = (gz_statep)file;
    if (state->mode != GZ_READ && state->mode != GZ_WRITE)
        return -1;

    /* make sure we haven't already allocated memory */
    if (state->size != 0)
        return -1;

    /* check and set requested size */
    if (size < 2)
        size = 2;               /* need two bytes to check magic header */
    state->want = size;
    return 0;
}

/* -- see zlib.h -- */
int ZEXPORT gzrewind(file)
    gzFile file;
{
    gz_statep state;

    /* get internal structure */
    if (file == NULL)
        return -1;
    state = (gz_statep)file;

    /* check that we're reading and that there's no error */
    if (state->mode != GZ_READ ||
            (state->err != Z_OK && state->err != Z_BUF_ERROR))
        return -1;

    /* back up and start over */
    if (LSEEK(state->fd, state->start, SEEK_SET) == -1)
        return -1;
    gz_reset(state);
    return 0;
}

/* -- see zlib.h -- */
z_off64_t ZEXPORT gzseek64(file, offset, whence)
    gzFile file;
    z_off64_t offset;
    int whence;
{
    unsigned n;
    z_off64_t ret;
    gz_statep state;

    /* get internal structure and check integrity */
    if (file == NULL)
        return -1;
    state = (gz_statep)file;
    if (state->mode != GZ_READ && state->mode != GZ_WRITE)
        return -1;

    /* check that there's no error */
    if (state->err != Z_OK && state->err != Z_BUF_ERROR)
        return -1;

    /* can only seek from start or relative to current position */
    if (whence != SEEK_SET && whence != SEEK_CUR)
        return -1;

    /* normalize offset to a SEEK_CUR specification */
    if (whence == SEEK_SET)
        offset -= state->x.pos;
    else if (state->seek)
        offset += state->skip;
    state->seek = 0;

    /* if within raw area while reading, just go there */
    if (state->mode == GZ_READ && state->how == COPY &&
            state->x.pos + offset >= 0) {
        ret = LSEEK(state->fd, offset - state->x.have, SEEK_CUR);
        if (ret == -1)
            return -1;
        state->x.have = 0;
        state->eof = 0;
        state->past = 0;
        state->seek = 0;
        gz_error(state, Z_OK, NULL);
        state->strm.avail_in = 0;
        state->x.pos += offset;
        return state->x.pos;
    }

    /* calculate skip amount, rewinding if needed for back seek when reading */
    if (offset < 0) {
        if (state->mode != GZ_READ)         /* writing -- can't go backwards */
            return -1;
        offset += state->x.pos;
        if (offset < 0)                     /* before start of file! */
            return -1;
        if (gzrewind(file) == -1)           /* rewind, then skip to offset */
            return -1;
    }

    /* if reading, skip what's in output buffer (one less gzgetc() check) */
    if (state->mode == GZ_READ) {
        n = GT_OFF(state->x.have) || (z_off64_t)state->x.have > offset ?
            (unsigned)offset : state->x.have;
        state->x.have -= n;
        state->x.next += n;
        state->x.pos += n;
        offset -= n;
    }

    /* request skip (if not zero) */
    if (offset) {
        state->seek = 1;
        state->skip = offset;
    }
    return state->x.pos + offset;
}

/* -- see zlib.h -- */
z_off_t ZEXPORT gzseek(file, offset, whence)
    gzFile file;
    z_off_t offset;
    int whence;
{
    z_off64_t ret;

    ret = gzseek64(file, (z_off64_t)offset, whence);
    return ret == (z_off_t)ret ? (z_off_t)ret : -1;
}

/* -- see zlib.h -- */
z_off64_t ZEXPORT gztell64(file)
    gzFile file;
{
    gz_statep state;

    /* get internal structure and check integrity */
    if (file == NULL)
        return -1;
    state = (gz_statep)file;
    if (state->mode != GZ_READ && state->mode != GZ_WRITE)
        return -1;

    /* return position */
    return state->x.pos + (state->seek ? state->skip : 0);
}

/* -- see zlib.h -- */
z_off_t ZEXPORT gztell(file)
    gzFile file;
{
    z_off64_t ret;

    ret = gztell64(file);
    return ret == (z_off_t)ret ? (z_off_t)ret : -1;
}

/* -- see zlib.h -- */
z_off64_t ZEXPORT gzoffset64(file)
    gzFile file;
{
    z_off64_t offset;
    gz_statep state;

    /* get internal structure and check integrity */
    if (file == NULL)
        return -1;
    state = (gz_statep)file;
    if (state->mode != GZ_READ && state->mode != GZ_WRITE)
        return -1;

    /* compute and return effective offset in file */
    offset = LSEEK(state->fd, 0, SEEK_CUR);
    if (offset == -1)
        return -1;
    if (state->mode == GZ_READ)             /* reading */
        offset -= state->strm.avail_in;     /* don't count buffered input */
    return offset;
}

/* -- see zlib.h -- */
z_off_t ZEXPORT gzoffset(file)
    gzFile file;
{
    z_off64_t ret;

    ret = gzoffset64(file);
    return ret == (z_off_t)ret ? (z_off_t)ret : -1;
}

/* -- see zlib.h -- */
int ZEXPORT gzeof(file)
    gzFile file;
{
    gz_statep state;

    /* get internal structure and check integrity */
    if (file == NULL)
        return 0;
    state = (gz_statep)file;
    if (state->mode != GZ_READ && state->mode != GZ_WRITE)
        return 0;

    /* return end-of-file state */
    return state->mode == GZ_READ ? state->past : 0;
}

/* -- see zlib.h -- */
const char * ZEXPORT gzerror(file, errnum)
    gzFile file;
    int *errnum;
{
    gz_statep state;

    /* get internal structure and check integrity */
    if (file == NULL)
        return NULL;
    state = (gz_statep)file;
    if (state->mode != GZ_READ && state->mode != GZ_WRITE)
        return NULL;

    /* return error information */
    if (errnum != NULL)
        *errnum = state->err;
    return state->err == Z_MEM_ERROR ? "out of memory" :
                                       (state->msg == NULL ? "" : state->msg);
}

/* -- see zlib.h -- */
void ZEXPORT gzclearerr(file)
    gzFile file;
{
    gz_statep state;

    /* get internal structure and check integrity */
    if (file == NULL)
        return;
    state = (gz_statep)file;
    if (state->mode != GZ_READ && state->mode != GZ_WRITE)
        return;

    /* clear error and end-of-file */
    if (state->mode == GZ_READ) {
        state->eof = 0;
        state->past = 0;
    }
    gz_error(state, Z_OK, NULL);
}

/* Create an error message in allocated memory and set state->err and
   state->msg accordingly.  Free any previous error message already there.  Do
   not try to free or allocate space if the error is Z_MEM_ERROR (out of
   memory).  Simply save the error message as a static string.  If there is an
   allocation failure constructing the error message, then convert the error to
   out of memory. */
void ZLIB_INTERNAL gz_error(state, err, msg)
    gz_statep state;
    int err;
    const char *msg;
{
    size_t bufsize = 0;
    
    /* free previously allocated message and clear */
    if (state->msg != NULL) {
        if (state->err != Z_MEM_ERROR) free(state->msg);
        state->msg = NULL;
    }

    /* if fatal, set state->x.have to 0 so that the gzgetc() macro fails */
    if (err != Z_OK && err != Z_BUF_ERROR) state->x.have = 0;

    /* set error code, and if no message, then done */
    state->err = err;
    if (msg == NULL) return;

    /* for an out of memory error, return literal string when requested */
    if (err == Z_MEM_ERROR) return;

    /* construct error message with path */
    bufsize = strlen(state->path) + strlen(msg) + 3;
    if ((state->msg = (char *)malloc(bufsize)) == NULL) {
        state->err = Z_MEM_ERROR; return;
    }
    
    /* Here, we simplify the code, snprintf must exist */
#if defined(_WIN32)
    _snprintf_s(state->msg, bufsize, _TRUNCATE, "%s%s%s", 
        state->path, ": ", msg);
#else
    snprintf(state->msg, bufsize, "%s%s%s", state->path, ": ", msg);
#endif
}

#ifndef INT_MAX
/* portably return maximum value for an int (when limits.h presumed not
   available) -- we need to do this to cover cases where 2's complement not
   used, since C standard permits 1's complement and sign-bit representations,
   otherwise we could just use ((unsigned)-1) >> 1 */
unsigned ZLIB_INTERNAL gz_intmax()
{
    unsigned p, q;

    p = 1;
    do {
        q = p; p <<= 1; p++;
    } while (p > q);
    return q >> 1;
}
#endif

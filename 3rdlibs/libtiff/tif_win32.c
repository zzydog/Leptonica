/* $Id: tif_win32.c,v 1.41 2015-08-23 20:12:44 bfriesen Exp $ */

/*
 * Copyright (c) 1988-1997 Sam Leffler
 * Copyright (c) 1991-1997 Silicon Graphics, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software 
 * and its documentation for any purpose is hereby granted without fee, 
 * provided that (i) the above copyright notices and this permission 
 * notice appear in all copies of the software and related documentation,
 * and (ii) the names of Sam Leffler and Silicon Graphics may not be used 
 * in any advertising or publicity relating to the software without the 
 * specific, prior written permission of Sam Leffler and Silicon Graphics.
 * 
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY 
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  
 * 
 * IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
 * ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY 
 * KIND, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR 
 * PROFITS, WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON 
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE 
 * OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * TIFF Library Win32-specific Routines.  Adapted from tif_unix.c 4/5/95 
 * by Scott Wagner (wagner@itek.com), Itek Graphix, Rochester, NY USA
 */

#include <io.h>
#include <windows.h>

#include "tiffiop.h"


typedef union _file_client {
    int fd; thandle_t hd;
} file_client_t, *p_file_client_t;


static tmsize_t
_tiffReadProc_(HANDLE hfile, void* buffer, tmsize_t size)
{
    /* 
     * tmsize_t is 64bit on 64bit systems, but the WinAPI 
     * ReadFile takes 32bit sizes, so we loop through the 
     * data in suitable 32bit sized chunks 
     */
    uint8* ma; uint64 mb; DWORD n; DWORD offset; tmsize_t p;
    ma = (uint8*)buffer; mb = size; p = 0;
    while (mb > 0)
    {
        n = 0x80000000UL;
        if ((uint64)n > mb) n = (DWORD)mb;
        if (!ReadFile(hfile, (LPVOID)ma, n, &offset, NULL)) 
            return(0);
        ma += offset; mb -= offset; p += offset;
        if (offset < n) break;  /* Finished: use '<' instead */
    }
    return(p);
}
static tmsize_t
_tiffReadProc1(thandle_t hfile, void* buffer, tmsize_t size)
{
    file_client_t file; HANDLE hFile; file.hd = hfile;
    hFile = (thandle_t)_get_osfhandle( file.fd );
    if (hFile == INVALID_HANDLE_VALUE) return 0;
    else { return _tiffReadProc_(hFile, buffer, size); }
}
#if defined(USE_WIN32_FILEIO)
//#define _tiffReadProc2 _tiffReadProc_ (TDMGCC Warining)
static tmsize_t
_tiffReadProc2(thandle_t hfile, void* buffer, tmsize_t size)
{
    return _tiffReadProc_((HANDLE)hfile, buffer, size); 
}
#else
static tmsize_t
_tiffReadProc2(thandle_t hfile, void* buffer, tmsize_t size)
{
    HANDLE hFile = (HANDLE)_get_osfhandle(_fileno(hfile));
    if (hFile == INVALID_HANDLE_VALUE) return 0;
    else { return _tiffReadProc_(hfile, buffer, size); }
}
#endif


static tmsize_t
_tiffWriteProc_(HANDLE hfile, void* buffer, tmsize_t size)
{
    /* 
     * tmsize_t is 64bit on 64bit systems, but the WinAPI 
     * WriteFile takes 32bit sizes, so we loop through the 
     * data in suitable 32bit sized chunks 
     */
    uint8* ma; uint64 mb; DWORD n; DWORD offset; tmsize_t p;
    ma = (uint8*)buffer; mb = size; p = 0;
    while (mb > 0)
    {
        n=0x80000000UL;
        if ((uint64)n > mb) n = (DWORD)mb;
        if (!WriteFile(hfile, (LPVOID)ma, n, &offset, NULL)) 
            return(0);
        ma += offset; mb -= offset; p += offset;
        if (offset < n) break;  /* Finished: use '<' instead */
    }
    return(p);
}
static tmsize_t
_tiffWriteProc1(thandle_t hfile, void* buffer, tmsize_t size)
{
    file_client_t file; HANDLE hFile; file.hd = hfile;
    hFile = (thandle_t)_get_osfhandle( file.fd );
    if (hFile == INVALID_HANDLE_VALUE) return 0;
    else { return _tiffWriteProc_(hFile, buffer, size); }
}
#if defined(USE_WIN32_FILEIO)
//#define _tiffWriteProc2 _tiffWriteProc_ (TDMGCC Warining)
static tmsize_t
_tiffWriteProc2(thandle_t hfile, void* buffer, tmsize_t size)
{
    return _tiffWriteProc_((HANDLE)hfile, buffer, size);
}
#else
static tmsize_t
_tiffWriteProc2(thandle_t hfile, void* buffer, tmsize_t size)
{
    HANDLE hFile = (HANDLE)_get_osfhandle(_fileno(hfile));
    if (hFile == INVALID_HANDLE_VALUE) return 0;
    else { return _tiffWriteProc_(hfile, buffer, size); }
}
#endif


static uint64
_tiffSeekProc_(HANDLE hfile, uint64 offset, int whence)
{
    LARGE_INTEGER offli; DWORD dwMoveMethod;
    offli.QuadPart = offset;
    switch(whence) {
        case SEEK_SET:  dwMoveMethod = FILE_BEGIN;  break;
        case SEEK_CUR:  dwMoveMethod = FILE_CURRENT;break;
        case SEEK_END:  dwMoveMethod = FILE_END;    break;
        default:        dwMoveMethod = FILE_BEGIN;  break;
    }
    offli.LowPart = SetFilePointer(
        hfile, offli.LowPart, &offli.HighPart, dwMoveMethod
    );
    if(offli.LowPart == INVALID_SET_FILE_POINTER)
        if(GetLastError() != NO_ERROR) offli.QuadPart = 0;
    return(offli.QuadPart);
}
static uint64
_tiffSeekProc1(thandle_t hfile, uint64 offset, int whence)
{
    file_client_t file; HANDLE hFile; file.hd = hfile;
    hFile = (thandle_t)_get_osfhandle( file.fd );
    if (hFile == INVALID_HANDLE_VALUE) return 0;
    else { return _tiffSeekProc_(hFile, offset, whence); }
}
#if defined(USE_WIN32_FILEIO)
//#define _tiffSeekProc2 _tiffSeekProc_ (TDMGCC Warining)
static uint64
_tiffSeekProc2(thandle_t hfile, uint64 offset, int whence)
{
    return _tiffSeekProc_((HANDLE)hfile, offset, whence);
}
#else
static uint64
_tiffSeekProc2(thandle_t hfile, uint64 offset, int whence)
{
    HANDLE hFile = (HANDLE)_get_osfhandle(_fileno(hfile));
    if (hFile == INVALID_HANDLE_VALUE) return 0;
    else { return _tiffSeekProc_(hFile, offset, whence); }
}
#endif


static int _tiffCloseProc_(HANDLE hfile)
{
    return (CloseHandle(hfile) ? 0 : -1);
}
static int _tiffCloseProc1(thandle_t hfile)
{
    file_client_t file; file.hd = hfile; 
    return _close(file.fd); /* Simply return its value */
}
#if defined(USE_WIN32_FILEIO)
//#define _tiffCloseProc2 _tiffCloseProc_ (TDMGCC Warining)
static int _tiffCloseProc2(thandle_t hfile)
{
    return _tiffCloseProc_((HANDLE)hfile);
}
#else
static int _tiffCloseProc2(thandle_t hfile)
{
    return fclose((FILE *)hfile);
}
#endif


static uint64 _tiffSizeProc_(HANDLE hfile)
{
    ULARGE_INTEGER m;
    m.LowPart = GetFileSize(hfile, &m.HighPart);
    return(m.QuadPart);
}
static uint64 _tiffSizeProc1(thandle_t hfile)
{
    file_client_t file; HANDLE hFile; file.hd = hfile;
    hFile = (thandle_t)_get_osfhandle( file.fd );
    if (hFile == INVALID_HANDLE_VALUE) return 0;
    else { return _tiffSizeProc_(hFile); }
}
#if defined(USE_WIN32_FILEIO)
//#define _tiffSizeProc2 _tiffSizeProc_ (TDMGCC Warining)
static uint64 _tiffSizeProc2(thandle_t hfile)
{
    return _tiffSizeProc_((HANDLE)hfile);
}
#else
static uint64 _tiffSizeProc2(thandle_t hfile)
{
    HANDLE hFile = (HANDLE)_get_osfhandle(_fileno(hfile));
    if (hFile == INVALID_HANDLE_VALUE) return 0;
    else { return _tiffSizeProc_(hFile); }
}
#endif


static int
_tiffDummyMapProc_(HANDLE hfile, void** pbase, toff_t* psize)
{
    (void) hfile; (void) pbase; (void) psize; return (0);
}
static int
_tiffDummyMapProc1(thandle_t hfile, void** pbase, toff_t* psize)
{
    (void) hfile; (void) pbase; (void) psize; return (0);
}
#if defined(USE_WIN32_FILEIO)
//#define _tiffDummyMapProc2 _tiffDummyMapProc_ (TDMGCC Warining)
static int
_tiffDummyMapProc2(thandle_t hfile, void** pbase, toff_t* psize)
{
    return _tiffDummyMapProc_((HANDLE)hfile, pbase, psize);
}
#else
static int
_tiffDummyMapProc2(thandle_t hfile, void** pbase, toff_t* psize)
{
    (void) hfile; (void) pbase; (void) psize; return (0);
}
#endif


/*
 * From "Hermann Josef Hill" <lhill@rhein-zeitung.de>:
 *
 * Windows uses both a handle and a pointer for file mapping,
 * but according to the SDK documentation and Richter's book
 * "Advanced Windows Programming" it is safe to free the handle
 * after obtaining the file mapping pointer
 *
 * This removes a nasty OS dependency and cures a problem
 * with Visual C++ 5.0
 */
static int
_tiffMapProc_(HANDLE hfile, void** pbase, toff_t* psize)
{
    uint64 size; tmsize_t sizem; HANDLE hMapFile;

    size = _tiffSizeProc_(hfile); sizem = (tmsize_t)size;
    if((uint64)sizem != size) return (0);

    /* 
     * By passing in 0 for the maximum file size, it specifies 
     * that we create a file mapping object for the full file 
     * size. 
     */
    hMapFile = CreateFileMapping(
        hfile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hMapFile == NULL) return (0);
    *pbase = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
    CloseHandle(hMapFile);
    if (*pbase == NULL) return (0);
    *psize = size; return(1);
}
static int
_tiffMapProc1(thandle_t hfile, void** pbase, toff_t* psize)
{
    file_client_t file; HANDLE hFile; file.hd = hfile;
    hFile = (thandle_t)_get_osfhandle( file.fd );
    if (hFile == INVALID_HANDLE_VALUE) return 0;
    else { return _tiffMapProc_(hFile, pbase, psize); }
}
#if defined(USE_WIN32_FILEIO)
//#define _tiffMapProc2 _tiffMapProc_ (TDMGCC Warining)
static int
_tiffMapProc2(thandle_t hfile, void** pbase, toff_t* psize)
{
    return _tiffMapProc_((HANDLE)hfile, pbase, psize);
}
#else
static int
_tiffMapProc2(thandle_t hfile, void** pbase, toff_t* psize)
{
    HANDLE hFile = (HANDLE)_get_osfhandle(_fileno(hfile));
    if (hFile == INVALID_HANDLE_VALUE) return 0;
    else { return _tiffMapProc_(hFile, pbase, psize); }
}
#endif


static void
_tiffDummyUnmapProc_(HANDLE hfile, void* base, toff_t size)
{
    (void) hfile; (void) base; (void) size;
}
static void
_tiffDummyUnmapProc1(thandle_t hfile, void* base, toff_t size)
{
    (void) hfile; (void) base; (void) size;
}
#if defined(USE_WIN32_FILEIO)
//#define _tiffDummyUnmapProc2 _tiffDummyUnmapProc_ 
static void
_tiffDummyUnmapProc2(thandle_t hfile, void* base, toff_t size)
{
    _tiffDummyUnmapProc_((HANDLE)hfile, base, size);
}
#else
static void
_tiffDummyUnmapProc2(thandle_t hfile, void* base, toff_t size)
{
    (void) hfile; (void) base; (void) size;
}
#endif


static void
_tiffUnmapProc_(HANDLE hfile, void* base, toff_t size)
{
    (void) hfile; (void) size; UnmapViewOfFile(base);
}
static void
_tiffUnmapProc1(thandle_t hfile, void* base, toff_t size)
{
    (void) hfile; (void) size; UnmapViewOfFile(base);
}
#if defined(USE_WIN32_FILEIO)
//#define _tiffUnmapProc2 _tiffUnmapProc_ (TDMGCC Warining)
static void
_tiffUnmapProc2(thandle_t hfile, void* base, toff_t size)
{
    _tiffUnmapProc_((HANDLE)hfile, base, size);
}
#else
static void
_tiffUnmapProc2(thandle_t hfile, void* base, toff_t size)
{
    HANDLE hFile = (HANDLE)_get_osfhandle(_fileno(hfile));
    if (hFile == INVALID_HANDLE_VALUE) return 0;
    else { return _tiffUnmapProc_(hFile, base, size); }
}
#endif


/*
 * Open a TIFF file descriptor for read/writing.
 * Note that TIFFFdOpen and TIFFOpen recognise the character 
 * 'u' in the mode string, which forces the file to be opened 
 * unmapped.
 */
TIFF* TIFFFdOpen(int hfile, const char* name, const char* mode)
{
    TIFF* tif; int m; int fSuppressMap = 0; file_client_t file;
    for (m = 0; mode[m] != 0; ++m) {
        if (mode[m] == 'u') { fSuppressMap = 1; break; }
    }
    /* FIXED: WIN64 cast to pointer warning */
    file.fd = hfile;
    tif = TIFFClientOpen( name, mode, file.hd, 
             _tiffReadProc1, _tiffWriteProc1,
             _tiffSeekProc1, _tiffCloseProc1, _tiffSizeProc1,
             fSuppressMap ? _tiffDummyMapProc1 : _tiffMapProc1,
             fSuppressMap ? _tiffDummyUnmapProc1 : _tiffUnmapProc1);
    if (tif) tif->tif_fd = hfile;
    return (tif);
}
TIFF* TIFFHdOpen(thandle_t hfile, const char* name, const char* mode)
{
    int m; TIFF* tif; int fSuppressMap = 0;
    for (m=0; mode[m]!=0; m++) {
        if (mode[m]=='u') { fSuppressMap=1; break; }
    }
    /* Here, We don't need the file descriptor, return directly */
    tif = TIFFClientOpen(name, mode, hfile, 
             _tiffReadProc2, _tiffWriteProc2,
             _tiffSeekProc2, _tiffCloseProc2, _tiffSizeProc2,
             fSuppressMap ? _tiffDummyMapProc2 : _tiffMapProc2,
             fSuppressMap ? _tiffDummyUnmapProc2 : _tiffUnmapProc2);
    return (tif);
}

#ifndef _WIN32_WCE

/*
 * Open a TIFF file for read/writing.
 */
TIFF* TIFFOpen(const char* name, const char* mode)
{
    static const char module[] = "TIFFOpen";
    thandle_t hd; int m = 0; DWORD dwMode; TIFF* tif;

    m = _TIFFgetMode(mode, module);

    switch(m) {
        case O_RDONLY:              dwMode = OPEN_EXISTING; break;
        case O_RDWR:                dwMode = OPEN_ALWAYS;   break;
        case O_RDWR|O_CREAT:        dwMode = OPEN_ALWAYS;   break;
        case O_RDWR|O_TRUNC:        dwMode = CREATE_ALWAYS; break;
        case O_RDWR|O_CREAT|O_TRUNC:dwMode = CREATE_ALWAYS; break;
        default:                    return ((TIFF*)0);
    }

    hd = (thandle_t)CreateFileA(name,
        (m==O_RDONLY) ? GENERIC_READ : (GENERIC_READ|GENERIC_WRITE),
        FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, dwMode,
        (m==O_RDONLY) ? FILE_ATTRIBUTE_READONLY : FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (hd == INVALID_HANDLE_VALUE) {
        TIFFErrorExt(0, module, "%s: Cannot open", name);
        return ((TIFF *)0);
    }

    /* 
     * FIXED: WIN64 cast from pointer to int warning 
     * Here, We use the new function 'TIFFHdOpen' instead. As I know 
     * about the tiff library, file descriptor is useless, so we can
     * simply ignore it. ('TIFFHdOpen' will do so)
     * But you should know that 'TIFFFileno' and 'TIFFSetFileno' can
     * not be used in the tiff library.
     */
    tif = TIFFHdOpen(hd, name, mode);
    if(!tif) CloseHandle(hd);
    return tif;
}


/*
 * Open a TIFF file with a Unicode filename, for read/writing.
 */
TIFF* TIFFOpenW(const wchar_t* name, const char* mode)
{
    static const char module[] = "TIFFOpenW";
    thandle_t fd = NULL; 
    char *mbname = NULL; TIFF *tif;
    int m; DWORD dwMode; int mbsize; 

    m = _TIFFgetMode(mode, module);

    switch(m) {
        case O_RDONLY:              dwMode = OPEN_EXISTING; break;
        case O_RDWR:                dwMode = OPEN_ALWAYS;   break;
        case O_RDWR|O_CREAT:        dwMode = OPEN_ALWAYS;   break;
        case O_RDWR|O_TRUNC:        dwMode = CREATE_ALWAYS; break;
        case O_RDWR|O_CREAT|O_TRUNC:dwMode = CREATE_ALWAYS; break;
        default:                    return ((TIFF*)0);
    }

    fd = (thandle_t)CreateFileW(name,
        (m==O_RDONLY) ? GENERIC_READ: (GENERIC_READ|GENERIC_WRITE),
        FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, dwMode,
        (m==O_RDONLY) ? FILE_ATTRIBUTE_READONLY : FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (fd == INVALID_HANDLE_VALUE) {
        TIFFErrorExt(0, module, "%S: Cannot open", name);
        return ((TIFF *)0);
    }

    mbsize = WideCharToMultiByte(
                 CP_ACP, 0, name, -1, NULL, 0, NULL, NULL);
    if (mbsize > 0) {
        mbname = (char *)_TIFFmalloc(mbsize);
        if(!mbname) {
            TIFFErrorExt(0, module,
                "Can't allocate space for filename conversion");
            return ((TIFF*)0);
        }
        WideCharToMultiByte(
            CP_ACP, 0, name, -1, mbname, mbsize, NULL, NULL);
    }

    /* FIXED: WIN64 cast from pointer to int warning */
    tif = TIFFHdOpen(fd, (mbname==NULL) ? "<unknown>" : mbname, mode);
    if(!tif) CloseHandle(fd);
    _TIFFfree(mbname); return tif;
}

#endif /* ndef _WIN32_WCE */

void* _TIFFmalloc(tmsize_t s)
{
    if (s == 0) return ((void *) NULL);
    return (malloc((size_t) s));
}

void _TIFFfree(void* p)
{
	free(p);
}

void* _TIFFrealloc(void* p, tmsize_t s)
{
	return (realloc(p, (size_t) s));
}

void _TIFFmemset(void* p, int v, tmsize_t c)
{
	memset(p, v, (size_t) c);
}

void _TIFFmemcpy(void* d, const void* s, tmsize_t c)
{
	memcpy(d, s, (size_t) c);
}

int _TIFFmemcmp(const void* p1, const void* p2, tmsize_t c)
{
	return (memcmp(p1, p2, (size_t) c));
}

#ifndef _WIN32_WCE

static void
Win32WarningHandler(const char* module, const char* fmt, va_list ap)
{
#ifndef TIF_PLATFORM_CONSOLE
    LPCSTR szTmpModule = NULL;
    LPCSTR szTitleText = "%s Warning";
    LPCSTR szDefaultModule = "LIBTIFF";
    SIZE_T nBufSize = 0; int txtlen = 0; 
    LPSTR szText = NULL; LPSTR szTitle = NULL;

    szTmpModule = (module == NULL) ? szDefaultModule : module;
    nBufSize = (
        strlen(szTmpModule)+strlen(szTitleText)+strlen(fmt)+2048);
    /* Plz use malloc instead if you want to simplify the code */
    szTitle = (LPSTR)HeapAlloc( 
        GetProcessHeap(), HEAP_ZERO_MEMORY, nBufSize);
    if (szTitle == NULL) return ; 

    txtlen = _snprintf_s(
        szTitle, nBufSize, _TRUNCATE, szTitleText, szTmpModule); 
    if (errno == 0 && txtlen >= 0) { 
        szText = szTitle + txtlen + 1;
        txtlen = _vsnprintf_s(
            szText, nBufSize-txtlen, _TRUNCATE, fmt, ap);
        if (errno == 0 && txtlen >= 0) {
            MessageBoxA (
                GetFocus(), szText, szTitle, MB_OK|MB_ICONINFORMATION
            );
        }
    }
    /* 
     * The logic here, which handle the failure of HeapFree is not 
     * tested, but you can simply take a look at this article:
     * https://blogs.msdn.microsoft.com/oldnewthing/20120106-00/?p=8663
     */
    if (!HeapFree(GetProcessHeap(), 0, szTitle)) {
        // ...
    }
#else
	if (module != NULL) fprintf_s(stderr, "%s: ", module);
	fprintf_s(stderr, "Warning, "); 
    vfprintf_s(stderr, fmt, ap); fprintf_s(stderr, ".\n");
#endif        
}
TIFFErrorHandler _TIFFwarningHandler = Win32WarningHandler;

static void
Win32ErrorHandler(const char* module, const char* fmt, va_list ap)
{
#ifndef TIF_PLATFORM_CONSOLE
    LPCSTR szTmpModule = NULL;
    LPCSTR szTitleText = "%s Error";
    LPCSTR szDefaultModule = "LIBTIFF";
    SIZE_T nBufSize = 0; int txtlen = 0; 
    LPSTR szText = NULL; LPSTR szTitle = NULL;
    
    szTmpModule = (module == NULL) ? szDefaultModule : module;
    nBufSize = (
        strlen(szTmpModule)+strlen(szTitleText)+strlen(fmt)+2048);
    /* Plz use malloc instead if you want to simplify the code */
    szTitle = (LPSTR)HeapAlloc( 
        GetProcessHeap(), HEAP_ZERO_MEMORY, nBufSize);
    if (szTitle == NULL) return ; 

    txtlen = _snprintf_s(
        szTitle, nBufSize, _TRUNCATE, szTitleText, szTmpModule); 
    if (errno == 0 && txtlen >= 0) { 
        szText = szTitle + txtlen + 1;
        txtlen = _vsnprintf_s(
            szText, nBufSize-txtlen, _TRUNCATE, fmt, ap);
        if (errno == 0 && txtlen >= 0) {
            MessageBoxA (
                GetFocus(), szText, szTitle, MB_OK|MB_ICONINFORMATION
            );
        }
    }
    /* 
     * The logic here, which handle the failure of HeapFree is not 
     * tested, but you can simply take a look at this article:
     * https://blogs.msdn.microsoft.com/oldnewthing/20120106-00/?p=8663
     */
    if (!HeapFree(GetProcessHeap(), 0, szTitle)) {
        // ...
    }
#else
    if (module != NULL) fprintf_s(stderr, "%s: ", module);
	fprintf_s(stderr, "Error, "); 
    vfprintf_s(stderr, fmt, ap); fprintf_s(stderr, ".\n");
#endif        
}
TIFFErrorHandler _TIFFerrorHandler = Win32ErrorHandler;

#endif /* ndef _WIN32_WCE */

/* vim: set ts=8 sts=8 sw=8 noet: */
/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 8
 * fill-column: 78
 * End:
 */

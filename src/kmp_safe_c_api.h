/* <copyright>
    Copyright (c) 1997-2015 Intel Corporation.  All Rights Reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

      * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
      * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
      * Neither the name of Intel Corporation nor the names of its
        contributors may be used to endorse or promote products derived
        from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
    A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
    HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

</copyright> */

#ifndef KMP_SAFE_C_API_H
#define KMP_SAFE_C_API_H

//
// Replacement for banned C API
//

// Not every unsafe call listed here is handled now, but keeping everything
// in one place should be handy for future maintenance.
#if KMP_OS_WINDOWS

# define RSIZE_MAX_STR ( 4UL << 10 ) // 4KB

// _malloca was suggested, but it is not a drop-in replacement for _alloca
# define KMP_ALLOCA                  _alloca

# define KMP_MEMCPY_S                memcpy_s
# define KMP_SNPRINTF                sprintf_s
# define KMP_SSCANF                  sscanf_s
# define KMP_STRCPY_S                strcpy_s
# define KMP_STRNCPY_S               strncpy_s

// Use this only when buffer size is unknown
# define KMP_MEMCPY(dst, src, cnt)   memcpy_s(dst, cnt, src, cnt)

# define KMP_STRLEN(str)             strnlen_s(str, RSIZE_MAX_STR)

// Use this only when buffer size is unknown
# define KMP_STRNCPY(dst, src, cnt)  strncpy_s(dst, cnt, src, cnt)

// _TRUNCATE insures buffer size > max string to print.
# define KMP_VSNPRINTF(dst, cnt, fmt, arg)  vsnprintf_s(dst, cnt, _TRUNCATE, fmt, arg)

#else // KMP_OS_WINDOWS

// For now, these macros use the existing API.

# define KMP_ALLOCA                         alloca
# define KMP_MEMCPY_S(dst, bsz, src, cnt)   memcpy(dst, src, cnt)
# define KMP_SNPRINTF                       snprintf
# define KMP_SSCANF                         sscanf
# define KMP_STRCPY_S(dst, bsz, src)        strcpy(dst, src) 
# define KMP_STRNCPY_S(dst, bsz, src, cnt)  strncpy(dst, src, cnt)
# define KMP_VSNPRINTF                      vsnprintf
# define KMP_STRNCPY                        strncpy
# define KMP_STRLEN                         strlen
# define KMP_MEMCPY                         memcpy

#endif // KMP_OS_WINDOWS

#endif // KMP_SAFE_C_API_H

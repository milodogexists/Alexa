/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef _A_OSAPI_H_
#define _A_OSAPI_H_

#if defined(__linux__) && !defined(LINUX_EMULATION)
#include "../os/linux/include/osapi_linux.h"
#endif

#ifdef ATHR_WM_NWF
#include "../os/windows/include/osapi.h"
#include "../os/windows/include/netbuf.h"
#endif

#ifdef ATHR_CE_LEGACY
#include "../os/windows/include/osapi.h"
#include "../os/windows/include/netbuf.h"
#endif

#ifdef REXOS
#include "../os/rexos/include/common/osapi_rexos.h"
#endif

#if defined ART_WIN
#include "../os/win_art/include/osapi_win.h"
#include "../os/win_art/include/netbuf.h"
#endif

#ifdef ATHR_WIN_NWF
#include "../os/windows/include/win/osapi_win.h"
#include "../os/windows/include/netbuf.h"
#endif

#endif /* _OSAPI_H_ */

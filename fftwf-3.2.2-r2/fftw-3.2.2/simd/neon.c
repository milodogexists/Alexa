/*
 * Copyright (c) 2011 Vesperix Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#include "ifftw.h"
#include "simd.h"

#if HAVE_NEON

#ifdef __ARM_NEON__

int RIGHT_CPU(void)
{
     return 1;
}

#else

#include <signal.h>
#include <setjmp.h>

static jmp_buf jb;

static void sighandler(int x)
{
     longjmp(jb, 1);
}

static int really_have_neon(void)
{
     void (*oldsig)(int);
     oldsig = signal(SIGILL, sighandler);
     if (setjmp(jb)) {
	  signal(SIGILL, oldsig);
	  return 0;
     } else {
	  __asm__ __volatile__ ("vmov.f32 d0, #0.0\n" : : : "d0");
	  signal(SIGILL, oldsig);
	  return 1;
     }
     return 0;
}

int RIGHT_CPU(void)
{
     static int init = 0, res;
     if (!init) {
	  res = really_have_neon();
	  init = 1;
     }
     return res;
}

#endif /* __ARM_NEON__ */

#endif /* HAVE_NEON */



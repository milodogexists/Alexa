/* Machine-dependent ELF indirect relocation inline functions.
   SPARC 64-bit version.
   Copyright (C) 2010 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#ifndef _DL_IREL_H
#define _DL_IREL_H

#include <stdio.h>
#include <unistd.h>
#include <dl-plt.h>

#define ELF_MACHINE_IRELA	1

static inline void
__attribute ((always_inline))
elf_irela (const Elf64_Rela *reloc)
{
  unsigned int r_type = (reloc->r_info & 0xff);

  if (__builtin_expect (r_type == R_SPARC_IRELATIVE, 1))
    {
      Elf64_Addr *const reloc_addr = (void *) reloc->r_offset;
      Elf64_Addr value = ((Elf64_Addr (*) (void)) reloc->r_addend) ();
      *reloc_addr = value;
    }
  else if (__builtin_expect (r_type == R_SPARC_JMP_IREL, 1))
    {
      Elf64_Addr *const reloc_addr = (void *) reloc->r_offset;
      Elf64_Addr value = ((Elf64_Addr (*) (void)) reloc->r_addend) ();
      struct link_map map = { .l_addr = 0 };

      /* 'high' is always zero, for large PLT entries the linker
	 emits an R_SPARC_IRELATIVE.  */
      sparc64_fixup_plt (&map, reloc, reloc_addr, value, 0, 0);
    }
  else if (r_type == R_SPARC_NONE)
    ;
  else
    __libc_fatal ("unexpected reloc type in static binary");
}

#endif /* dl-irel.h */

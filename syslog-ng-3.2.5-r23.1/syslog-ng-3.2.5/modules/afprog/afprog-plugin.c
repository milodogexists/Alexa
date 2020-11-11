/*
 * Copyright (c) 2002-2010 BalaBit IT Ltd, Budapest, Hungary
 * Copyright (c) 1998-2010 Balázs Scheidler
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As an additional exemption you are allowed to compile & link against the
 * OpenSSL libraries as published by the OpenSSL project. See the file
 * COPYING for details.
 *
 */

#include "cfg-parser.h"
#include "plugin.h"

extern CfgParser afprog_parser;

static Plugin afprog_plugins[] =
{
  {
    .type = LL_CONTEXT_SOURCE,
    .name = "program",
    .parser = &afprog_parser,
  },
  {
    .type = LL_CONTEXT_DESTINATION,
    .name = "program",
    .parser = &afprog_parser,
  },
};

gboolean
afprog_module_init(GlobalConfig *cfg, CfgArgs *args)
{
  plugin_register(cfg, afprog_plugins, G_N_ELEMENTS(afprog_plugins));
  return TRUE;
}

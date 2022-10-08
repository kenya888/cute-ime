/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   cuteime                                                                  *
 *   Copyright (C) 2010-2016 by Tasuku Suzuki <stasuku@gmail.com>            *
 *   Copyright (C) 2016 by Takahiro Hashimoto <kenya888@gmail.com>           *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Lesser Public License as          *
 *   published by the Free Software Foundation; either version 2 of the      *
 *   License, or (at your option) any later version.                         *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU Lesser General Public License for more details.                     *
 *                                                                           *
 *   You should have received a copy of the GNU Lesser General Public        *
 *   License along with this program; if not, write to the                   *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <gtk/gtk.h>
#include <gtk/gtkimmodule.h>

#include <cuteimedebug.h>
#include "../cuteimeimcontext.h"

G_MODULE_EXPORT void g_io_im_cuteime_load(GIOModule *module)
{
    g_type_module_use(G_TYPE_MODULE(module));
    cuteime_im_context_register_type(G_TYPE_MODULE(module));
    g_io_extension_point_implement(GTK_IM_MODULE_EXTENSION_POINT_NAME, CUTEIME_IM_CONTEXT_TYPE,
                                    "cuteime",10);
}


G_MODULE_EXPORT void g_io_im_cuteime_unload(GIOModule *module)
{
  g_type_module_unuse(G_TYPE_MODULE(module));
}

G_MODULE_EXPORT const char * im_get_context_id(int *argc, char ***argv)
{
  GtkIMContext *context;
  char *preedit_string = NULL;
  PangoAttrList *preedit_attrs = NULL;
  const char *context_id;

  gtk_init();
  context = gtk_im_multicontext_new();
  gtk_im_context_get_preedit_string(context, &preedit_string, &preedit_attrs, 0);
  context_id = gtk_im_multicontext_get_context_id(GTK_IM_MULTICONTEXT(context));
  return context_id;
}

G_MODULE_EXPORT char ** g_io_module_query(void)
{
  char *eps[] = {GTK_IM_MODULE_EXTENSION_POINT_NAME, NULL};

  return g_strdupv(eps);
}

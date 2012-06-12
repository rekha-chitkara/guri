/* g-uri.h
 *
 * Copyright (C) 2012 Christian Hergert <chris@dronelabs.com>
 *
 * This file is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef G_URI_H
#define G_URI_H

#include <glib.h>

G_BEGIN_DECLS

typedef struct _GUri GUri;

const gchar *g_uri_get_fragment    (const GUri  *uri);
const gchar *g_uri_get_hostname    (const GUri  *uri);
const gchar *g_uri_get_param       (const GUri  *uri,
                                    const gchar *param);
GHashTable  *g_uri_get_params      (const GUri  *uri);
const gchar *g_uri_get_password    (const GUri  *uri);
const gchar *g_uri_get_path        (const GUri  *uri);
gint         g_uri_get_port        (const GUri  *uri);
const gchar *g_uri_get_scheme      (const GUri  *uri);
const gchar *g_uri_get_username    (const GUri  *uri);
GUri        *g_uri_new             (void);
GUri        *g_uri_new_from_string (const gchar *uri);
GUri        *g_uri_ref             (GUri        *uri);
void         g_uri_set_hostname    (GUri        *uri,
                                    const gchar *hostname);
void         g_uri_set_param       (GUri        *uri,
                                    const gchar *param,
                                    const gchar *value);
void         g_uri_set_password    (GUri        *uri,
                                    const gchar *password);
void         g_uri_set_path        (GUri        *uri,
                                    const gchar *path);
void         g_uri_set_port        (GUri        *uri,
                                    gushort      port);
void         g_uri_set_scheme      (GUri        *uri,
                                    const gchar *scheme);
void         g_uri_set_username    (GUri        *uri,
                                    const gchar *username);
gchar       *g_uri_to_string       (const GUri  *uri);
void         g_uri_unref           (GUri        *uri);

G_END_DECLS

#endif /* G_URI_H */

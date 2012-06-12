/* g-uri.c
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

#include "g-uri.h"

struct _GUri
{
   volatile gint ref_count;

   gchar *fragment;
   gchar *hostname;
   gchar *password;
   gchar *path;
   gushort port;
   gchar *scheme;
   gchar *username;
   GHashTable *params;
};

GUri *
g_uri_new (void)
{
   GUri *uri;

   uri = g_slice_new0(GUri);
   uri->ref_count = 1;

   return uri;
}

const gchar *
g_uri_get_fragment (const GUri *uri)
{
   g_return_val_if_fail(uri, NULL);
   return uri->fragment;
}

const gchar *
g_uri_get_hostname (const GUri *uri)
{
   g_return_val_if_fail(uri, NULL);
   return uri->hostname;
}

const gchar *
g_uri_get_param (const GUri  *uri,
                 const gchar *param)
{
   const gchar *ret = "";

   g_return_val_if_fail(uri, NULL);

   if (uri->params) {
      ret = g_hash_table_lookup(uri->params, param);
   }

   return ret;
}

const gchar *
g_uri_get_password (const GUri *uri)
{
   g_return_val_if_fail(uri, NULL);
   return uri->password;
}

const gchar *
g_uri_get_path (const GUri *uri)
{
   g_return_val_if_fail(uri, NULL);
   return uri->path;
}

gint
g_uri_get_port (const GUri *uri)
{
   g_return_val_if_fail(uri, 0);
   return uri->port;
}

const gchar *
g_uri_get_scheme (const GUri *uri)
{
   g_return_val_if_fail(uri, NULL);
   return uri->scheme;
}

const gchar *
g_uri_get_username (const GUri *uri)
{
   g_return_val_if_fail(uri, NULL);
   return uri->username;
}

void
g_uri_set_fragment (GUri        *uri,
                    const gchar *fragment)
{
   g_return_if_fail(uri);
   g_free(uri->fragment);
   uri->fragment = g_strdup(fragment);
}

void
g_uri_set_hostname (GUri        *uri,
                    const gchar *hostname)
{
   g_return_if_fail(uri);
   g_free(uri->hostname);
   uri->hostname = g_strdup(hostname);
}

void
g_uri_set_password (GUri        *uri,
                    const gchar *password)
{
   g_return_if_fail(uri);
   g_free(uri->password);
   uri->password = g_strdup(password);
}

void
g_uri_set_path (GUri        *uri,
                const gchar *path)
{
   g_return_if_fail(uri);
   g_free(uri->path);
   uri->path = g_strdup(path);
}

void
g_uri_set_port (GUri    *uri,
                gushort  port)
{
   g_return_if_fail(uri);
   uri->port = port;
}

void
g_uri_set_scheme (GUri        *uri,
                  const gchar *scheme)
{
   g_return_if_fail(uri);
   g_free(uri->scheme);
   uri->scheme = g_strdup(scheme);
}

void
g_uri_set_username (GUri        *uri,
                    const gchar *username)
{
   g_return_if_fail(uri);
   g_free(uri->username);
   uri->username = g_strdup(username);
}

void
g_uri_set_param (GUri        *uri,
                 const gchar *param,
                 const gchar *value)
{
   g_return_if_fail(uri);
   g_return_if_fail(param);

   if (!uri->params) {
      uri->params = g_hash_table_new_full(g_str_hash,
                                          g_str_equal,
                                          g_free,
                                          g_free);
   }

   g_hash_table_insert(uri->params, g_strdup(param), g_strdup(value));
}

GHashTable *
g_uri_get_params (const GUri *uri)
{
   g_return_if_fail(uri);
   return uri->params;
}

gchar *
g_uri_to_string (const GUri *uri)
{
   GHashTableIter iter;
   const gchar *key;
   const gchar *value;
   GString *str = NULL;

   g_return_val_if_fail(uri, NULL);

   str = g_string_new(NULL);

   if (uri->scheme) {
      g_string_append_printf(str, "%s://", uri->scheme);
   }

   if (uri->username && uri->password) {
      g_string_append_printf(str, "%s:%s@", uri->username, uri->password);
   } else if (uri->username) {
      g_string_append_printf(str, "%s@", uri->username);
   }

   if (!uri->hostname) {
      goto failure;
   }

   g_string_append_printf(str, "%s", uri->hostname);

   if (uri->port) {
      g_string_append_printf(str, ":%hu", uri->port);
   }

   g_string_append_printf(str, "%s", uri->path ? uri->path : "/");

   if (uri->params && g_hash_table_size(uri->params)) {
      g_string_append(str, "?");
      g_hash_table_iter_init(&iter, uri->params);
      while (g_hash_table_iter_next(&iter,
                                    (gpointer *)&key,
                                    (gpointer *)&value)) {
         g_string_append_printf(str, "%s=%s&", key, value);
      }
      g_string_truncate(str, str->len - 1);
   }

   if (uri->fragment) {
      g_string_append_printf(str, "#%s",
                             (uri->fragment[0] == '#') ?
                              &uri->fragment[1] :
                              uri->fragment);
   }

   return g_string_free(str, FALSE);

failure:
   if (str) {
      g_string_free(str, TRUE);
   }

   return NULL;
}

GUri *
g_uri_ref (GUri *uri)
{
   g_return_val_if_fail(uri, NULL);
   g_return_val_if_fail(uri->ref_count > 0, NULL);
   g_atomic_int_inc(&uri->ref_count);
   return uri;
}

void
g_uri_unref (GUri *uri)
{
   g_return_if_fail(uri);
   g_return_if_fail(uri->ref_count > 0);

   if (g_atomic_int_dec_and_test(&uri->ref_count)) {
      g_free(uri->fragment);
      g_free(uri->hostname);
      g_free(uri->password);
      g_free(uri->path);
      g_free(uri->scheme);
      g_free(uri->username);
      g_hash_table_unref(uri->params);
      g_slice_free(GUri, uri);
   }
}

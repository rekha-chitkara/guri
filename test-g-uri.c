#include "g-uri.h"

static void
test1 (void)
{
   GUri *uri;
   gchar *str;

   uri = g_uri_new();
   g_uri_set_scheme(uri, "scheme");
   g_uri_set_username(uri, "username");
   g_uri_set_password(uri, "password");
   g_uri_set_hostname(uri, "hostname");
   g_uri_set_port(uri, 1234);
   g_uri_set_path(uri, "/some/path");
   g_uri_set_param(uri, "data", "buffer");
   g_uri_set_param(uri, "key", "value");
   g_uri_set_fragment(uri, "#abcdef");
   str = g_uri_to_string(uri);
   g_assert_cmpstr(str, ==, "scheme://username:password@hostname:1234/some/path?data=buffer&key=value#abcdef");
   g_free(str);
   g_uri_unref(uri);
}

gint
main (gint   argc,
      gchar *argv[])
{
   g_test_init(&argc, &argv, NULL);
   g_test_add_func("/Uri/basic", test1);
   return g_test_run();
}

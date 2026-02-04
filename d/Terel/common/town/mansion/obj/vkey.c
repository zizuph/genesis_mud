
inherit "/std/object.c";

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

create_object()
{
   set_short("small iron key");
   set_adj("small");
   set_long("A small iron key, with a small amount of rust.\n");
   set_name("virgins_key");
   add_name("key");
}



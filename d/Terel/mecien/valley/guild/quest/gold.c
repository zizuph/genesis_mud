/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/object";
#include <stdproperties.h>

create_object()
{
   set_name("gold");
   set_adj("piece of");
   add_name("piece of gold");
   add_name("mystic_quest_gold");
   set_long("This tiny piece of gold is very odd. Its shape being\n"
      + "like a triangle, but it looks quite rough and natural.\n");
   add_prop(OBJ_I_VALUE, 32);
}


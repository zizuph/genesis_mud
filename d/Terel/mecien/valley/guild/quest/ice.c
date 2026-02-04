/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/object";
#include <stdproperties.h>

create_object()
{
   set_name("ice");
   set_adj("cloudy");
    add_adj("piece of");
   add_name("mystic_quest_ice");
   set_long("A strange piece of cloudy ice. It is almost like\n"
     + "crystal, it does not melt.\n");
   add_prop(OBJ_I_VALUE, 1);
}


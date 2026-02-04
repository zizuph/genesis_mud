/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/object";
#include <stdproperties.h>

create_object()
{
   set_name("flower");
   set_adj("orange");
   add_name("aravene");
   add_name("mystic_quest_flower");
   set_long("A beautiful orange flower, it has a strange smell and is\n"
      + "warm to touch. The petals cast a slight red hue, it seems\n"
      + "to almost radiate light.\n");
   add_prop(OBJ_I_VALUE, 10);
}


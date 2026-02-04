/* Creative rights reserved to Mecien(Jeff Babcock) and team. */

inherit "/std/food";
#include <stdproperties.h>

create_food()
{
   set_name("bread");
   set_adj("unleavened");
   set_long("A large round loaf of unleavened bread. It has been specially\n"
      +"prepared by the mystics under silent vows.\n");
   set_amount(100);
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 80);
}

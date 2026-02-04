/* Creative rights reserved to Mecien(Jeff Babcock) and team. */

inherit "/std/food";
#include <stdproperties.h>

create_food()
{
   set_name("broth");
   set_adj("herb");
   set_long("A small cup of herb and vegetable broth.\n");
   set_amount(6);
   add_prop(OBJ_I_WEIGHT, 10);
   add_prop(OBJ_I_VOLUME, 3);
}

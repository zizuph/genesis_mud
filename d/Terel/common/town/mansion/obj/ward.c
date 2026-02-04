/*
 * An example bag, made by Nick
 */

inherit "/std/container";
#include <stdproperties.h>

void
create_container()
{
   set_name("wardrobe");
   set_long("This wardrobe contains the clothing of a servant of " +
    "this mansion.\n");

   add_prop(CONT_I_WEIGHT, 2500);
   add_prop(CONT_I_MAX_WEIGHT, 250000);
   add_prop(OBJ_I_NO_GET, 1);
   add_prop(CONT_I_VOLUME, 3000);
   add_prop(CONT_I_MAX_VOLUME, 250000);

}

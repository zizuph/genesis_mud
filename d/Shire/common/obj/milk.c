/*
 *   Milk, given by good ole Bessie herself.
 */

inherit "/std/drink";

#include "/sys/stdproperties.h"

create_drink() {
   set_name("milk");
   add_name("bessie's_milk");
   add_adj(({"fresh","wholesome"}));
   set_short("fresh wholesome milk");
   set_long("This is some of the freshest milk you've ever seen.\n");
   add_prop(OBJ_I_VALUE, 2);
   set_soft_amount(100);
   add_prop(OBJ_I_WEIGHT,560);
   add_prop(OBJ_I_VOLUME,205);
}

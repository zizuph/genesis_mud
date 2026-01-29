/*
 * Scavenger Hunt item
 * Finwe, October 2015
*/

inherit "/std/object";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void
create_object()
{

   set_name("spoon");

   set_short("wooden spoon");
   add_adj(({"wooden"}));

   set_long("This is a wooden spoon. The handle is long with a rounded head. The spoon is carved from oak and used in food preparation.\n");

   add_prop(OBJ_I_WEIGHT, 227);
   add_prop(OBJ_I_VALUE, 0);
}

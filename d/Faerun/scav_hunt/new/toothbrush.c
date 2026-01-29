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

   set_name("toothbrush");

   set_short("wooden toothbrush");
   add_adj(({"wooden"}));

   set_long("This is a small wooden toothbrush. It is a small brush with a long handed and used to brush teeth. The toothbrush looks well used.\n");

   add_prop(OBJ_I_WEIGHT, 227);
   add_prop(OBJ_I_VALUE, 0);
}

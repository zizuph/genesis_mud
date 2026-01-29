/*
 *  Pheasant.c  - food for the Ranger Inn.
 */

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("pheasant");
  add_name("plate");
   set_adj("hot");
   set_short("hot plate of fried pheasant");
   set_pshort("hot plates with fried pheasants");
   set_long(break_string(
    "The pheasant has been fried, and is deliciously served with "+
    "potatoes, sauce and a tad of garlic.\n",70));
   add_prop(OBJ_I_VALUE, 0);
  set_amount(125);
   add_prop(OBJ_I_WEIGHT,140);
   add_prop(OBJ_I_VOLUME,150);
}

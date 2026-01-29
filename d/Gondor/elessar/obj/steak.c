/*
 *  Steak.c  - food for the Rangers Inn.
 */

inherit "/std/food";
#include "/sys/stdproperties.h"

create_food() {
   set_name("steak");
  add_name("stag");
  add_name("plate");
   set_adj("stag");
   set_short("plate of hot stag steak");
   set_pshort("plates with hot stag steaks");
   set_long(break_string(
    "On the plate is a large steak of wild stag meat, served with "+
    "delicious wild sauce, potatoes, salad and jam.\n",70));
   add_prop(OBJ_I_VALUE, 0);
  set_amount(200);
   add_prop(OBJ_I_WEIGHT,175);
   add_prop(OBJ_I_VOLUME,200);
}

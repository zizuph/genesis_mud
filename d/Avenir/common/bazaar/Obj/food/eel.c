// file name: /d/Avenir/common/bazaar/Obj/food/eel.c
// creator(s): Ilyian, May 17, 1995
// last update:
// purpose: Food for the Dancing Potato inn
// note:
// bug(s):
// to-do:

inherit "/std/food";
#include "/sys/stdproperties.h"

create_food() {
   set_name("eel");
   add_name("meat");
   add_name("plate");
   set_adj("hot");
   set_short("plate of hot eel meat");
   set_pshort("plates with hot eel meat");
   set_long(
       "This is an enormous serving of hot eel meat, a delicacy in "+
       "some places. The watery eyes of the dead eel stare up at "+
       "you.\n");
   add_prop(OBJ_I_VALUE, 0);
   set_amount(560);
   add_prop(OBJ_I_WEIGHT,550);
   add_prop(OBJ_I_VOLUME,390);
}

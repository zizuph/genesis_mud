// file name: /d/Avenir/common/bazaar/Obj/food/fish.c
// creator(s): Ilyian, May 17, 1995
// last update:
// purpose: Food for the Dancing Potato inn
// note:
// bug(s):
// to-do:

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("fish");
   add_name("plate");
   set_adj("sweet-smelling");
   set_short("plate of sweet-smelling fish");
   set_pshort("plates of sweet-smelling fish");
   set_long(
     "You aren't sure what sort of fish this mouth-watering dish "+
     "was prepared with, but it smells wonderful! It is cooked in "+
     "a delicate and creamy sauce, with chopped potatos and carrots "+
     "on the side. It looks quite filling.\n");
   add_prop(OBJ_I_VALUE, 0);
   set_amount(350);
   add_prop(OBJ_I_WEIGHT,140);
   add_prop(OBJ_I_VOLUME,5000);
}

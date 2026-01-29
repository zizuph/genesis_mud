// file name: /d/Avenir/common/bazaar/Obj/food/mollusk.c
// creator(s): Ilyian, May 17, 1995
// last update:
// purpose: Food for the Dancing Potato inn
// note:
// bug(s):
// to-do:

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("mollusk");
   set_adj("boiled");
   set_short("boiled mollusk");
   set_pshort("boiled mollusks");
   set_long(
    "This is the boiled carcass of some unidentifiable mollusk. It smells "+
    "a bit strange, and you wonder what it was before it died. But "+
    "if you are hungry enough, it will make quite a good meal.\n");
   add_prop(OBJ_I_VALUE, 0);
  set_amount(150);
   add_prop(OBJ_I_WEIGHT,160);
   add_prop(OBJ_I_VOLUME,1000);
}

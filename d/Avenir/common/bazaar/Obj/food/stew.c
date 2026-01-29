
// file name: /d/Avenir/common/bazaar/Obj/food/stew.c
// creator(s): Ilyian, May 17, 1995
// last update:
// purpose: Food for the Dancing Potato inn
// note:
// bug(s):
// to-do:

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("stew");
  add_name("bowl");
   set_adj("potato");
   set_short("bowl of hot potato stew");
   set_pshort("bowls of hot potato stew");
   set_long(
    "This potato stew looks quite good, with steam rising up from "+
    "the broth, and freshly cooked potatos floating within.\n");
   add_prop(OBJ_I_VALUE, 0);
   set_amount(95);
   add_prop(OBJ_I_WEIGHT,120);
   add_prop(OBJ_I_VOLUME,5000);
}

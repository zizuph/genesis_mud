// file name: /d/Avenir/common/bazaar/Obj/food/soup.c
// creator(s): Ilyian, May 17, 1995
// last update:
// purpose: Food for the Dancing Potato inn
// note:
// bug(s):
// to-do:

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("soup");
  add_name("bowl");
   set_adj("hot", "fish");
   set_short("bowl of hot fish soup");
   set_pshort("bowls of hot fish soup");
   set_long(
      "The hot fish soup smells nice and wholesome, good if you "+
      "aren't terribly hungry, or if you have a small stomach.\n");
   add_prop(OBJ_I_VALUE, 0);
   set_amount(55);
   add_prop(OBJ_I_WEIGHT,80);
   add_prop(OBJ_I_VOLUME,5000);  // food shouldn't be so easy to carry!
}

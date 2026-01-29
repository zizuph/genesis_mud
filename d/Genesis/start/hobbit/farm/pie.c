/*
 *  Apple pie inside the kitchen stove of the farm.
 */

#pragma save_binary

inherit "/std/food";

#include "defs.h"
#include "/sys/stdproperties.h"

create_food() {
   set_short("apple pie");
   set_pshort("apple pies");
   set_name("pie");
   set_pname("pies");
   set_adj("apple");
   set_long(break_string(
      "The apple pie looks and smells delicious. It also seems "
    + "nutritious, since it has been made of fresh apples and "
    + "home-made dough. It looks like the ones your grandmother "
    + "used to make during your childhood.\n",70));

 /* Some properties of this apple pie */
   set_amount(300);                   /* 300 grams of food */
   add_prop(OBJ_I_WEIGHT, 300);       /* 300 grams of food */
   add_prop(OBJ_I_VOLUME, 700);       /* 0.7 Ltr           */
}


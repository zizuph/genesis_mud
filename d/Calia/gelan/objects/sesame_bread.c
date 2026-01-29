/*
 *   Sesame seed bread for the McCroissant bakery in Gelan
 *   Coded by Maniac
 */

inherit "/std/food";

#include <stdproperties.h>
#include "object.h"

create_food() {
   set_name("bread");
   add_name("loaf");
   set_adj("sesame");
   set_short("loaf of sesame bread");
   set_pshort("loaves of sesame bread");
   set_long("A large loaf of bread with sesame seeds on and in it.\n");
   add_prop(OBJ_I_VALUE, 155);
   set_amount(300);
}


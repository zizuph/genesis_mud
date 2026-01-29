/*
 *   Croissant for the McCroissant bakery in Gelan
 *   Coded by Maniac
 */

inherit "/std/food";

#include "object.h"
#include <stdproperties.h>

create_food() {
   set_name("croissant");
   set_short("croissant");
   set_pshort("croissants");
   set_long(
    "Ooh la la! Light buttered golden pastry in a nice crescent shape. It " +
    "looks rather fattening!\n");
   add_prop(OBJ_I_VALUE, 72);
   set_amount(200);
}


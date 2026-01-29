/*
 * Sandwich burger
 * Sold in the kiosk on the pier
 * Tapakah, 04/2009
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

void
create_food()
{
    set_short("salmon burger");
    set_pshort("salmon burgers");
    set_name("salmon");
    add_name("fish");
    add_name("burger");
    set_pname("burgers");
    set_long(
             "A square piece of salmon, sitting between two yellowish buns, "
             +"decorated by lettuce and tomatoes and featuring a drop of "
             +"catsup\n");
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 420);
    set_amount(100);
}

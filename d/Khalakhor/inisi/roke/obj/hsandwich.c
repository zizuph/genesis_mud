/*
 * Herring sandwich
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
    set_short("herring sandwich");
    set_pshort("herring sandwiches");
    set_name("herring");
    add_name("fish");
    add_name("sandwich");
    set_pname("sandwiches");
    set_long(
             "A white marinated fillet herring, in an oblong bun, with "
             +"a leaf of lettuce and a touch of mustard.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 120);
    set_amount(50);
}

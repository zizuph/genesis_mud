/*
 * Fried shrimps
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
    set_short("fried shrimps");
    set_pshort("fried shrimpses");
    set_name("shrimps");
    add_name("shellfish");
    add_adj("fried");
    set_pname("shrimpses");
    set_long(
             "An exceptionally large sized shrimp, stir-fried in vegetable "
             +"oil, looking very crispy and appetizing.\n");
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 120);
    set_amount(20);
}

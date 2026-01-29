/*
 * Spiced cookie
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
    set_short("spiced cookie");
    set_pshort("spiced cookies");
    set_name("cookie");
    add_adj("spiced");
    set_pname("cookies");
    set_long(
             "A large round cookie. You notice that the entire circle "
             +"is covered by multicolored dots of spices.\n");
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 150);
    set_amount(15);
}

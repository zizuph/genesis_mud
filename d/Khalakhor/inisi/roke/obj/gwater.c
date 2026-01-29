/*
 * Glass of water
 * Sold in a drink stall at the pier
 * TAPAKAH, 04/2009
 */

#pragma save_binary
#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>

void
create_drink()
{
    set_name("water");
    add_name("glass");
    set_adj("cold");
    add_adj("fresh");
    set_short("glass of water");
    set_pshort("glasses of water");
    set_long("A glass of fresh water.\n");
    set_soft_amount(30);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}

/*
 * Orange juice
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
    set_name("juice");
    add_name("orange");
    set_adj("orange");
    add_adj("squeezed");
    set_short("orange juice");
    set_pshort("orange juices");
    set_long("A freshly squeezed orange juice.\n");
    set_soft_amount(60);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 150);
}

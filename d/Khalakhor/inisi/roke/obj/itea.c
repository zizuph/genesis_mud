/*
 * Iced tea
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
    set_name("tea");
    set_adj("iced");
    add_adj("ice");
    set_short("iced tea");
    set_pshort("iced teas");
    set_long("A glass of golden iced tea, cold to be almost frozen.\n");
    set_soft_amount(80);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}

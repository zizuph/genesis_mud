/*
 * brew.c
 *
 * Used in nyreese/red_pub.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* gresolle 921113 */

#pragma save_binary
#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>

void
create_drink()
{
    set_soft_amount(540);       /* a pint */
    set_alco_amount(50);
    set_long("As you look at the bottle, you really wonder why you bought it.\n");
    set_name("brew");
    set_adj("strange");
    add_name("bottle");
    add_adj("bottle");
    add_adj("brew");

    set_short("bottle of strange brew");
    set_pshort("bottles of strange brew");

    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 600);
}

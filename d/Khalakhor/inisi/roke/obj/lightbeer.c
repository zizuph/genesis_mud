/*
 * lightbeer.c
 *
 * Used in nyreese/red_pub.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>

void
create_drink()
{
    set_soft_amount(100);
    set_alco_amount(6);
    set_name("beer");
    set_adj("light");
    set_short("light beer");
    set_pshort("light beers");
    set_long("This is really some great beer! Strangely enough, considering " +
             "the rest of the drinks in this bar.\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}

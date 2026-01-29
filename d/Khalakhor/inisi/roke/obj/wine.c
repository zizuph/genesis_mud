/*
 * wine.c
 *
 * Used in nyreese/cadu_inn.c
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
    set_soft_amount(200);
    set_alco_amount(20);
    set_name("wine");
    set_adj("sweet");
    set_short("sweet wine");
    set_pshort("sweet wines");
    set_long("It has a deep red colour and smells wonderful.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}

/*
 * fat.c
 *
 * Used in npc/child.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* Slice of fat, Used in Kato quest */

#pragma save_binary
#pragma strict_types

inherit "/std/food";
#include <stdproperties.h>
#include <macros.h>

void
create_food()
{
    set_name(({"fat", "piece"}));
    set_short("slice of fat");
    set_pshort("slices of fat");
    set_long("A piece of greasy fat torn out from a child \n");
    set_adj("greasy");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 80);
    set_amount(64);
}

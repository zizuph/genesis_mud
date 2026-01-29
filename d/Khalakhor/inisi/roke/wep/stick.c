/*
 * stick.c
 *
 * Used in npc/child.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* gresolle -92 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>

void
create_weapon()
{
    set_short("wooden stick");
    set_adj("wooden");
    set_name("stick");
    set_long("Sticks like this are normally found in the woods. " +
             "Someone, apparently a child, has attached a small " +
             "piece of wood at one of the ends, thus making it " +
             "into an wooden sword.\n");
    set_hit(1);
    set_pen(1);

    set_wt(W_SWORD);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
}

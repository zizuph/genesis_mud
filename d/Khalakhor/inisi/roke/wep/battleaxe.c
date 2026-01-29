/*
 * battleaxe.c
 *
 * Used in npc/sknight2.c npc/guard2.c
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
    set_short("mattock");
    set_name("mattock");
    set_long("This is a very nasty-looking axe. It is made of steel and " +
             "has two blades, one horizontal and one vertical.\n");
    set_hit(23);
    set_pen(28);

    set_wt(W_AXE);
    set_dt(W_SLASH | W_IMPALE | W_BLUDGEON);
    set_hands(W_RIGHT | W_LEFT);
}

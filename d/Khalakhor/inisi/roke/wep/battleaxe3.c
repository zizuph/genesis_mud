/*
 * battleaxe3.c
 *
 * Used in npc/guard3.c npc/campleader.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* gresolle -92 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_short("golden mattock");
    set_name("mattock");
    set_long("This is a very nasty-looking axe. It is made of gold and " +
             "has two blades, one horizontal and one vertical.\n");
    set_hit(26);
    set_pen(31);

    set_wt(W_AXE);
    set_dt(W_SLASH | W_IMPALE | W_BLUDGEON);
    set_hands(W_RIGHT | W_LEFT);
}

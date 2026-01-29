/*
 * sword.c
 *
 * Used in npc/sknight1.c npc/guard1.c
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
    set_short("broadsword");
    set_adj("broad");
    set_name(({"sword", "broadsword"}));
    set_long("It's a standard broadsword, manufactured on Gont, and " +
             "issued to most of the guards in the castle.\n");
    set_hit(24);
    set_pen(30);

    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_RIGHT);
}

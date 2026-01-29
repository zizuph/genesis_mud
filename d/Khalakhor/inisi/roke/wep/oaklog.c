/*
 * oaklog.c
 *
 * Used in npc/hoodman.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>

void
create_weapon()
{
    set_name("log");
    set_adj("oak");
    set_short("oak log");
    set_long("A good piece of hard oak.\n");

    set_hands(W_BOTH);
    set_hit(15);
    set_pen(10);

    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);
}

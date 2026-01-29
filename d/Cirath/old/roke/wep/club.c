/*
 * club.c
 *
 * Used in npc/bum.c npc/goblin1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>

void
create_weapon()
{
    set_name("club");
    set_adj("wooden");
    set_short("wooden club");
    set_long("This is simply a branch from a small tree.\n");

    set_hit(10);
    set_pen(10);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
}

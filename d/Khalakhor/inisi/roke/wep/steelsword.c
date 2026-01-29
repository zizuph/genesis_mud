/*
 * steelsword.c
 *
 * Used in npc/towerg3.c npc/towerg4.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* Glindor -93 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>

void
create_weapon()
{
    set_name("sword");
    set_short("steel sword");
    set_adj("steel");
    set_long("It's a steel sword, it looks very sharp.\n");
    set_hit(35);
    set_pen(35);

    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_RIGHT);
}

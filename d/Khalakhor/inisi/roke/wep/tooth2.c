/*
 * tooth2.c
 *
 * Used in npc/bore2.c
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
    set_name("tooth");
    set_adj("lethal");
    set_short("lethal tooth");
    set_long("A lethal Boretooth. It is made of some incredible hard alloy. " +
             "It looks like it could be used as a knife.\n");
    set_hit(18);
    set_pen(21);
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);
}

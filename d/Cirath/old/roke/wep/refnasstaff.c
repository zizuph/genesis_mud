/*
 * refnasstaff.c
 *
 * Used in npc/refnas.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* gresolle -92 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>

void
create_weapon()
{
    set_short("polished copper staff");
    set_adj("polished");
    add_adj("copper");
    set_name("staff");
    set_long("The staff is made of copper and polished very carefully.\n");

    set_hit(10);
    set_pen(10);

    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
}

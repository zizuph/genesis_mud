/*
 * k_morningstar.c
 *
 * Used in npc/knights.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* Calonderiel 94 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("morningstar");
    set_short("spiked morningstar");
    set_adj("spiked");
    set_long("The morningstar has a heavy metalball" +
             " with nasty looking spikes.\n");
    set_hit(24);
    set_pen(27);

    set_wt(W_CLUB);
    set_dt(W_BLUDGEON | W_IMPALE);
    set_hands(W_ANYH);

    add_prop(OBJ_I_VOLUME, 1045);
}

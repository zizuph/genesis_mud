/*
 * spear.c
 *
 * Used in npc/towerg1.c npc/towerg2.c npc/towerg3.c npc/kobold1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_short("iron spear");
    set_long("It has blood stains.\n");
    set_adj("iron");
    set_name("spear");

    set_hit(15);
    set_pen(15);

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 3);

    set_wt(W_POLEARM);
    set_dt(W_NO_DT);
    set_hands(W_BOTH);
}

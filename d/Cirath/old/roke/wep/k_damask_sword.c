/*
 * k_damask_sword.c
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
    set_name("sword");
    set_short("damask sword");
    set_adj("damask");
    set_long("A steel sword with a normal cross guard.\n" +
             "Along the blade runs a beautiful wavy pattern.\n");
    set_hit(32);
    set_pen(27);

    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_ANYH);

    add_prop(OBJ_I_VOLUME, 1100);
}

/*
 * k_battleaxe.c
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
    set_name("battleaxe");
    set_short("large battleaxe");
    add_name("axe");
    set_adj("large");
    set_long("A large battleaxe with a metal shaft.\n");
    set_hit(22);
    set_pen(29);

    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);

    add_prop(OBJ_I_VOLUME, 1280);
}

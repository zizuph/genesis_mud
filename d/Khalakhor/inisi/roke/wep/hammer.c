/*
 * hammer.c
 *
 * Used in npc/weaponsmith.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include "defs.h"
#include <stdproperties.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name("hammer");
    set_adj("heavy");
    set_short("heavy hammer");
    set_long("A heavy weaponsmith-hammer.\n");

    set_hands(W_ANYH);
    set_hit(15);
    set_pen(15);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);

    add_prop(OBJ_I_WEIGHT,8000);
    add_prop(OBJ_I_VOLUME,2000);
}

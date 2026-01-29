/*
 * halberd.c
 *
 * Used in npc/campguard.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name("halberd");
    set_adj("blood-stained");
    set_short("blood-stained halberd");
    set_long("An ordinary halberd, perfect for chopping off heads.\n");

    set_hands(W_BOTH);
    set_hit(35);
    set_pen(25);

    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 7200);

    set_wt(W_POLEARM);
    set_dt(W_SLASH);
}

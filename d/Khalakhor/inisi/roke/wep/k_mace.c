/*
 * k_mace.c
 *
 * Used in npc/knights.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* Calonderiel 94 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("mace");
    set_short("winged steel mace");
    set_adj("winged");
    add_adj("steel");
    set_long("A steel mace with a winged head.\n");
    set_hit(29);
    set_pen(20);

    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);

    add_prop(OBJ_I_VOLUME, 865);
}

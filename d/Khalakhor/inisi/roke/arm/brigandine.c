/*
 * brigandine.c
 *
 * Used in npc/sknight1.c npc/guard1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* gresolle -92 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("brigandine");
    set_short("iron brigandine");
    set_long("This is a standard brigandine, made from iron and leather.\n");
    set_adj("iron");

    set_ac(23);
    set_am(({1, 1, -2}));                  /* impale,slash,bludgeon */

    set_at(A_TORSO | A_ARMS);
    add_prop(OBJ_I_WEIGHT, 15000);
    add_prop(OBJ_I_VOLUME, 8000);
}

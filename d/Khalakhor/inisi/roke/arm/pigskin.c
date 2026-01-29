/*
 * pigskin.c
 *
 * Used in npc/ghoul.c npc/kobold2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* gresolle -92 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("leather armour");
    set_short("hardened leather armour");
    set_adj("hardened");
    set_long("This is the hardened skin from the war pig living on " +
             "the island Carisca.\n");

    set_ac(10);
    set_am(({-1, 1, 0}));       /* impale,slash,bludgeon */

    set_at(A_TORSO | A_ARMS);
    add_prop(OBJ_I_WEIGHT, 1700);
    add_prop(OBJ_I_VOLUME, 1000);
}

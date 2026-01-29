/*
 * doublemail.c
 *
 * Used in npc/sknight2.c npc/guard2.c npc/guard3.c npc/campleader.c
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
    set_name("mail");
    set_short("dwarven double silver mail");
    set_adj(({"dwarven", "silver", "double"}));
    set_long("This mail is made of several layers of silver.\n");

    set_ac(29);
    set_am(({-1, 1, 0}));                  /* impale,slash,bludgeon */

    set_at(A_TORSO | A_ARMS);
    add_prop(OBJ_I_WEIGHT, 17000);
    add_prop(OBJ_I_VOLUME, 8000);
}

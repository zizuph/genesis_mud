/*
 * cloak2.c
 *
 * Used in npc/hoodman.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("cloak");
    set_adj("green");
    set_short("green cloak");
    set_long("A cloak in the same colour as the forest.\n");

    set_ac(5);
    set_am(({0, 1, -1}));
    set_at(A_ROBE);

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
}

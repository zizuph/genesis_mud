/*
 * chelmet.c
 *
 * Used in npc/towerg1.c npc/towerg2.c npc/towerg3.c
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
    set_name("helmet");
    set_adj("copper");
    set_short("copper helmet");
    set_long("This is a helmet made of copper, mostly worn on the head.\n");
    set_ac(10);
    set_at(A_HEAD);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 5000);
}

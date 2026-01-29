/*
 * coat.c
 *
 * Used in npc/campguard.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 *
 * Updated and moved into new camp by Treacher, Aug 2021
 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

void
create_armour()
{
    set_name("coat");
    set_adj(({"thick", "leather"}));
    set_short("thick leather coat");
    set_long("This coat would be nice to wear in the Golbarian winter.\n");

    set_ac(10);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 7000);
}

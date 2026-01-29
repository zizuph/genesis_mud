/* 
 * /d/Gondor/guilds/rangers/obj/travel_cloak.c 
 *
 * Coded by ?
 *
 * The travel-cloaks of the rangers of the north
 */
inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("cloak");
    add_name("armour");
    set_adj("ranger");
    set_adj("travel-stained");
    set_adj("heavy");
    set_adj("dark-green");
    set_short("travel-stained dark-green cloak");
    set_long("This is a travel-stained, hooded cloak made of heavy " +
        "dark-green cloth.\n");
    set_default_armour(3, A_ROBE, (({ 0, 0, 1})), 0);
    add_prop(OBJ_I_WEIGHT, 360);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3) + random(20));
}

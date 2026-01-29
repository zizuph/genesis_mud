/*
 * Passage to Palanthas
 * Mortis, 3.2015
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>                                                   
#include <macros.h>
#include "../defs.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDPIER;

void
create_pier()
{
    set_short("Berth 17 - Palanthas");
    set_long("\n"
        + "An elaborate pier juts here into the Bay of Sparkle. Brilliant, "
        + "translucent white marble orbs top the rail points. A marblework "
        + "sign reads: \"Passage to Palanthas\" here.\n");

    add_item(({"pier", "elaborate pier"}), "Solid planks of weather treated "
        + "wood and great, round timbers of wood planted into the bay were "
        + "used to construct this sturdy pier. Marble orbs top the timbers "
        + "in a display of grandeur.\n");
    add_item(({"water"}), "The waves lap against the pier, splashing sea "
        + "water occasionally into the air. You need a boat to go out "
        + "there.\n");
    add_item(({"orb", "orbs", "marble orb", "marble orbs"}), "Spheres of "
        + "polished marble top the timbers of the pier and gleam from within "
        + "their translucent white centers.\n");
    add_item(({"sign", "marblework", "marblework sign"}), "A sign of "
        + "translucent, white marble here reads: \"Passage to Palanthas\"\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

    add_exit(TOWN_DIR + "pier16", "south");

    add_pier_entry(MASTER_OB(this_object()), "Sparkle", "Passage to Palanthas");
    initialize_pier();
}

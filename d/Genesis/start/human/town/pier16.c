/*
 * Passage to Faerie, cabotage travel
 * Tapakah, 10/2008
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"
#include "/d/Genesis/gsl_ships/ships.h"

#define RAVENLOFT_TESTER  "_ravenloft_tester"

inherit STDPIER;


public int
block_player()
{
    if (!this_player()->query_prop(RAVENLOFT_TESTER))
    {

        write("You think the new pier to the east looks too "
        +"fragile at the moment. You decide to wait until later.\n");
        return 1;
    }

    write("You bravely enter the new unfinished and fragile pier.\n");

    return 0;
}

void
create_pier()
{
    set_short("Berth 16 - Raumdor");
    set_long("\n"+
             "End of the south pier.\n" +
             "Looking east you see a new pier under construction.\n");

    add_item(({"pier" }),"It continues, but the new pier to the east looks unfinished and fragile.\n");
    add_item(({"works", "construction works"}), "The works are for expansion of the new pier to the east.\n");
    add_item(({"water" }),"The waves crash against the pier, spraying " +
        "sea water everywhere. You need a boat to go out there.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

    add_exit(TOWN_DIR + "pier18", "north");
    add_exit(TOWN_DIR + "pier17", "east", block_player);
    add_exit(TOWN_DIR + "pier15", "west");

    add_pier_entry(MASTER_OB(this_object()), "Sparkle", "Passage to Raumdor");
    initialize_pier();
}

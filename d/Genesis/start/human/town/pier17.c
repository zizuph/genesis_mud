/* /d/Genesis/start/human/town/pier17
 * Passage to Ravenloft
 * Nerull  2014
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
    set_short("Berth 17 - Ravenloft");
    set_long("\n"+
             "End of the south pier.\n" +
             "Looking east you see some construction works.\n");

    add_item(({"pier" }),"It ends here. However the construction works suggest future expansion to the east.\n");
    add_item(({"works", "construction works"}), "The works are for expansion of the pier to the east.\n");
    add_item(({"water" }),"The waves crash against the pier, spraying " +
        "sea water everywhere. You need a boat to go out there.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    //add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

    add_exit(TOWN_DIR + "pier16", "west");

    add_pier_entry(MASTER_OB(this_object()), "Sparkle", "Passage to Ravenloft");
    initialize_pier();
}


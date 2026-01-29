#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/std/boats/std_boat_defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit BLOODSEA_NEW_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

string *herbs = HERB_MASTER->query_herbs( ({ "oceanfloat", }) );

void
reset_sea_room()
{
    set_searched(0);

    return;
}

void
create_sea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"water", "sea"}), "The water within the Bloodsea has "+
        "a strange and reddish colour. Rumour has it that the colour "+
        "is the result of the blood of many victims who lost their "+
        "lives during Krynn's most terrible hour, though it "+
        "could be the clay stirred up from the sea bottom by the "+
        "maelstrom.\n");
    add_item(({"kern","coastline","jagged coastline","grasslands"}),
        "To the south and west is a jagged coastline, beyond which the " +
        "grasslands of the ogre empire of Kern stretch as far " +
        "as the eye can see.\n");
    add_item(({"seaport","port","ogrebond","berths","dock","traders",
        "slavers","ogre slavers","military vessels","vessels",
        "black dragonarmy"}),
        "Along the coastline here is the small city of Ogrebond, one " +
        "of the few ogre seaports on the Rugged Coast. From what you " +
        "see the port is bustling with traders, ogre slavers, and " +
        "military vessels of the Black Dragonarmy. Unfortunately " +
        "you can see no berths available to dock here.\n");

    add_row_exit(FROOM + "4b", "west", 0, 1);
    add_row_exit(FROOM + "5c", "north", 0, 1);
    add_row_exit(FROOM + "4d", "east", 0, 1);
    add_row_exit(FROOM + "3d", "southeast", 0, 1);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    // Set the sailing skill required to sail to this room.
    set_sailing_difficulty(CONDITIONS_CHALLENGING);

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("The waters along the coastline of Kern " +
        "are particularly treacherous. You don't have the skill to " +
        "navigate a ship here!\n");
    set_sailing_difficulty_message("You navigate skillfully through the " +
        "treacherous waters along the coastline of Kern.\n");

    set_sink_path("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"sea","water"}), 2);

    reset_sea_room();

}

int
no_go()
{
    write("You try and sail in that direction, however the current and wind created by a " +
       "mighty storm agressively drives you back!\n");
    return 1;
}

void
set_sink_path(string sp)
{
    sink_path = "/d/Ansalon/balifor/flotsam/room/bottom_of_bay";
}

string
short_descr()
{
    return bloodsea_short()+ ", near the seaport of Ogrebond";
}
 
string
long_descr()
{
    return bloodsea_desc()+ "To the south and west is a jagged coastline, beyond " +
        "which you can make out the grasslands of the ogre empire of Kern. Along " +
        "the coastline here is the seaport of Ogrebond. "
        +query_sailing_difficulty_desc()+ "\n";
}
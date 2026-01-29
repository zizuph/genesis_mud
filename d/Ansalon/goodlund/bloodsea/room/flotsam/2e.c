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
    add_item(({"coastline","wild coastline","ogrelands","the ogrelands",
        "kern"}),
        "West of the bay you can make out the wild coastline of the " +
        "Ogrelands, the beginning of the ogre empire of Kern.\n");
    add_item(({"blood bay","bay","balifor","thick forests","forests"}),
        "To your southwest opens a deep and relatively calm body of " +
        "water sheltered between the wild coastline of the Ogrelands " +
        "and the thick forests of Balifor. Blood Bay is deep, " +
        "allowing ships of all sizes to escape from the rough " +
        "conditions of the Blood Sea.\n");

    add_row_exit(FROOM + "2d", "west", 0, 1);
    add_row_exit(FROOM + "3e", "north", 0, 1);
    add_row_exit(FROOM + "2f", "east", "@@no_go");
    add_row_exit("/d/Krynn/south_courrain/room/s_courrain-12-13-c", "southeast", 0, 1);
    add_row_exit(FROOM + "1d", "southwest", 0, 1);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    // Set the sailing skill required to sail to this room.
    set_sailing_difficulty(CONDITIONS_CHALLENGING);

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("The waters along the coastline of Balifor " +
        "are particularly treacherous. You don't have the " +
        "skill to navigate a ship here!\n");
    set_sailing_difficulty_message("You navigate skillfully through these " +
        "challenging waters.\n");

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
    return bloodsea_short()+ ", near the entry to Blood Bay";
}
 
string
long_descr()
{
    return bloodsea_desc()+ "To your south and southwest opens the calmer waters " +
        "of Blood Bay, providing sailors some relief. "
        +query_sailing_difficulty_desc()+ "\n";
}
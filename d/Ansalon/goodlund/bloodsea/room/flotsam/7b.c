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
    add_item(({"peninsula","kern","pines","kern peninsula", "trees",
               "ferns","endscape woods","woods","forest"}),
        "To the west is a peninsula covered with hardy pines and " +
        "exotic ferns, making up what is known as the Endscape " +
        "Woods. This forest makes up the most northeastern " +
        "part of the ogre empire of Kern.\n");

    add_row_exit(CROOM + "3x", "northeast", 0, 1);
    add_row_exit(FROOM + "6a", "southwest", 0, 1);
    add_row_exit(FROOM + "7c", "east", 0, 1);
    add_row_exit(FROOM + "6b", "south", 0, 1);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    // Set the sailing skill required to sail to this room.
    set_sailing_difficulty(CONDITIONS_CHALLENGING);

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("The waters around the penisula of Kern " +
        "are particularly treacherous. You don't have the skill to " +
        "navigate through that way!\n");
    set_sailing_difficulty_message("You navigate skillfully through the " +
        "treacherous waters along the peninsula of Kern.\n");

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
    return bloodsea_short()+ ", near the peninsula of Kern";
}
 
string
long_descr()
{
    return bloodsea_desc()+ "To the west rises the peninsula of " +
        "Kern, where hardy pines and exotic ferns grow in abundance. "
        +query_sailing_difficulty_desc()+ "\n";
}
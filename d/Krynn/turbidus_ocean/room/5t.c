#include "/d/Krynn/common/defs.h"
#include "/d/Calia/sys/water.h"
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

inherit SAIL_ROOM_BASE;

#include "/d/Krynn/common/herbsearch.h"

#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

string *herbs = HERB_MASTER->query_herbs( ({ "intertide", }) );

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
 
    add_item(({"turbidus ocean","ocean","sea"}),
        "To your north stretches the Turbidus Ocean - a massive body of water " +
        "that extends from the Courrain Ocean in the east, across northern " +
        "Ansalon to the Sirrion Sea in the west.\n");
    add_item(({"reef","great reef","coral","maze"}),
        "To your west is a great reef, a maze of coral that would take a " +
        "skilled sailor to navigate. You have no doubt the reef holds " +
        "the wrecks of many unfortunate or foolish captains who were not up to " +
        "the task.\n");
    add_item(({"wrecks","ships"}),
        "You can see no wrecks from here, but assume the great reef would hold " +
        "many sunken ships of the unfortunate or foolish captains.\n");

    add_row_exit(ROOM + "6t", "north", 0, 1);
    add_row_exit(ROOM + "6s", "northwest", 0, 1);
    add_row_exit(REEF + "reef_entry_east", "west", 0, 1);
    add_row_exit(ROOM + "4t", "south", 0, 1);
    add_row_exit(ROOM + "4s", "southwest", 0, 1);
    add_row_exit(ROOM + "5u", "east", 0, 1);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    set_sink_path("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"sea","water"}), 2);

    reset_sea_room();
}

string
short_descr()
{
    return "on the edge of a great reef in the Turbidus Ocean";
}
 
string
long_descr()
{
    return turbidus_sea_desc() + "To your west is the edge of a great reef, a " +
        "maze of corals that make the waters around you rough and potentially " +
        "dangerous to the inexperienced sailor. "+
        query_sailing_difficulty_desc()+ "\n";
}
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
 
    add_item(({"deep water bay","deep bay","bay","bay of branchala",
        "inlet","water","deep water inlet"}),
        "The Bay of Branchala is a deep water inlet of the Turbidus Ocean. " +
        "On either side of the bay rise towering cliffs of white rock.\n");
    add_item(({"towering cliffs","white cliffs","cliffs","white rock",
        "rock","rocks","white rocks", "entry"}),
        "Towering cliffs of white rock rise on either side of the bay's entry, " +
        "looming so high that they make even the tallest ship seem tiny and " +
        "fragile. The white rock has been weathered to a breathtaking shine, " +
        "so impressive that even a master painter would struggle to capture " +
        "its beauty.\n");
    add_item(({"turbidus ocean","ocean","sea"}),
        "To your north the Turbidus Ocean begins - a massive body of water " +
        "that stretches from the Courrain Ocean in the east, across northern " +
        "Ansalon to the Sirrion Sea in the west.\n");
    add_item(({"reef","great reef","coral","maze"}),
        "To your north is a great reef, a natural " +
        "barrier that protects the bay to your south from wild storms blowing in " +
        "from the Turbidus Ocean to your north. It would take a skilled sailor " +
        "to navigate the maze of coral, and you have no doubt the reef holds " +
        "the wrecks of many unfortunate or foolish captains who were not up to " +
        "the task.\n");
    add_item(({"wrecks","ships"}),
        "You can see no wrecks from here, but assume the great reef would hold " +
        "many sunken ships of the unfortunate or foolish captains.\n");

    add_row_exit(ROOM + "4q", "east", 0, 1);
    add_row_exit(REEF + "reef_entry_south", "north", 0, 1);
    add_row_exit(ROOM + "4o", "west", 0, 1);
    add_row_exit(ROOM + "3p", "south", 0, 1);

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
    return "Bay of Branchala";
}
 
string
long_descr()
{
    return "You find yourself floating at the entry of a deep water inlet of " +
        "the Turbidus Ocean, the Bay of Branchala. On either side of the entry " +
        "rise towering cliffs of white rock, with the bay continuing south. " +
        "To your north begins a great reef, creating a natural barrier from " +
        "storms for the bay but also making the waters around you rough " +
        "and potentially dangerous to the inexperienced sailor. "+
        query_sailing_difficulty_desc()+ "\n";
}
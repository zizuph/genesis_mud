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

    add_item(({"palanthas harbour","harbour","palanthas", "city"}),
        "To your south opens the harbour of Palanthas the Beautiful, one of " +
        "the largest cities in Ansalon.\n"); 
    add_item(({"deep water bay","deep bay","bay","bay of branchala",
        "inlet","water","deep water inlet"}),
        "The Bay of Branchala is a deep water inlet of the Turbidus Ocean. " +
        "On either side of the bay rise towering cliffs of white rock.\n");
    add_item(({"towering cliffs","white cliffs","cliffs","white rock",
        "rock","rocks","white rocks"}),
        "On either side of the bay rise towering cliffs of white rock, looming " +
        "so high that they make even the tallest ship seem tiny and fragile. " +
        "The white rock has been weathered to a breathtaking shine, so " +
        "impressive that even a master painter would struggle to capture " +
        "its beauty.\n");
    add_item(({"turbidus ocean","ocean","sea"}),
        "You cannot see the Turbidus Ocean from here, but it is to your " +
        "north.\n");
    add_item(({"breakwater","extensive breakwater","opening","stone wall",
        "wall","low stone wall","low wall"}),
        "An extensive breakwater has been built about a mile from the docks " +
        "to your south. Towers that currently stand empty dot this low stone " +
        "wall, ready to be filled with archers and mages should trouble come " +
        "sailing down the bay. An opening to the south allows ships to enter " +
        "the harbour.\n");
    add_item(({"guard towers","towers"}),
        "Along the breakwater are guard towers - currently empty, but quickly " +
        "stationed with archers and mages if the city becomes threatened from " +
        "the sea.\n");

    add_row_exit(ROOM + "3p", "east", 0, 1);
    add_row_exit(ROOM + "4n", "northwest", 0, 1);
    add_row_exit(ROOM + "4o", "north", 0, 1);
    add_row_exit("/d/Krynn/solamn/palanthas/shipping/p01", "south", 0, 1);

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
    return "You find yourself floating on a deep water inlet of the Turbidus " +
        "Ocean, the Bay of Branchala. On either side of you to the east and west " +
        "rise towering cliffs of white rock. To your south is the opening of a " +
        "breakwater to the harbour of the famed City of Palanthas, while " +
        "to your north the bay eventually opens to the sea. "+
        query_sailing_difficulty_desc()+ "\n";
}
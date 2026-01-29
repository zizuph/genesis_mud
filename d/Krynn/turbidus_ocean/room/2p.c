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

    add_item(({"palanthas harbour","harbour","palanthas"}),
        "Surrounding you is the deep water bay of Palanthas Harbour. To your " +
        "south sprawls Palanthas the Beautiful, one of the largest cities in " +
        "Ansalon.\n"); 
    add_item(({"deep water bay","deep bay","bay","bay of branchala"}),
        "The Bay of Branchala is a deep water inlet of the Turbidus Ocean. " +
        "The harbour is protected from the worst of the elements by an " +
        "extensive breakwater to your north.\n");
    add_item(({"turbidus ocean","ocean"}),
        "You cannot see the Turbidus Ocean from here, but it is to your " +
        "north.\n");
    add_item(({"breakwater","extensive breakwater","opening","stone wall",
        "wall","low stone wall","low wall"}),
        "An extensive breakwater has been built about a mile from the docks " +
        "to your north. Towers that currently stand empty dot this low stone " +
        "wall, ready to be filled with archers and mages should trouble come " +
        "sailing down the bay. An opening to the north allows ships to leave " +
        "the harbour.\n");
    add_item(({"guard towers","towers"}),
        "Along the breakwater are guard towers - currently empty, but quickly " +
        "stationed with archers and mages if the city becomes threatened from " +
        "the sea.\n");
    add_item(({"tides"}),
        "The tides seem to be favourable right now to be sail out of the " +
        "harbour.\n");

    add_row_exit(ROOM + "3p", "north", 0, 1);
    add_row_exit(ROOM + "2q", "east", 0, 1);
    add_row_exit("/d/Krynn/solamn/palanthas/shipping/p01", "west", 0, 1);

    // add_swim_exit("/d/Krynn/solamn/palanthas/shipping/p01", "west", "@@swim_off", 1);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    set_sink_path("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"sea","water"}), 2);

    reset_sea_room();
}

int
swim_off()
{
   write("You swim back to the pier.\n");
   return 0;
}

string
short_descr()
{
    return "Palanthas Harbour";
}
 
string
long_descr()
{
    return "You are in Palanthas Harbour, a deep water bay protected " +
        "by an extensive breakwater built about a mile from the docks " +
        "themselves. An opening to the north allows access to the Bay " +
        "of Branchala when the tides are right. "+
        query_sailing_difficulty_desc()+ "\n";
}
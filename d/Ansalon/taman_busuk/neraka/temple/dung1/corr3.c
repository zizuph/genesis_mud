#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple which " +
        "leads off both east and west. Both the floor and walls are " +
        "bare. To the north is an archway leading into another " +
        "corridor and to the south are a pair of large metal doors.\n");

    add_item(({"door", "doors", "metal door", "metal doors"}),
        "To the south stands a pair of large metal doors. Delicate " +
        "patterns depicting dragons intertwined adore the doors. Eerie " +
        "light as well as occasional puffs of gray smoke sips through " +
        "the small space between the ground and the doors, as if " +
        "something is brewing behind.\n");
    add_item("archway", "The archway is decorated with smooth black " +
        "stone with small carvings.\n");
    add_item(({"carvings", "pattern", "starfall"}),
        "The carvings on the archway make up a pattern of starfall.\n");
    add_cmd_item(({"door", "doors", "metal door", "metal doors"}), "open",
        "The doors will not budge.\n");

    add_exit( DUNGONE  + "corr11", "north");
    add_exit( DUNGONE  + "corr4.c", "east" );
    add_exit( DUNGONE  + "corr2.c", "west" );
}

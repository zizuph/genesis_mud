#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(37);
	set_mirkwood_location(LOCATION_EAST_EDGE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p37", "southeast", "@@block@@",2,1);
    add_exit("p37", "south", "@@block@@",2,1);
    add_exit("p37", "northeast", "@@river@@",2,1);
    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r04/f37", "north", "@@river@@",2,1);
    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r04/f36", "northwest", "@@river@@",2,1);
    add_exit("p38", "east", "@@path@@");
    add_exit("p36", "west");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r20/f36", "southwest");

    add_long("To the north, you can see the wide, rushing waters of a " +
        "large river as it cuts through the forest.",
        ({LIGHT_MIDDAY, LIGHT_BRIGHT}));
   
}

int
path()
{
write("It seems as if the forest river has flooded here, preventing " +
    "you from going any further east and leaving Mirkwood.\n");
return 1;
}

int
river()
{
write("The forest river is too wide to cross here, you will have to go in " +
    "a different direction.\n");
return 1;
}

int
block()
{
write("It seems as if the forest river has flooded here, preventing " +
    "you from going any further east and leaving Mirkwood.\n");
return 1;
}
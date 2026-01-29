#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "path";

void create_mirkwood_south_forest_path_room() {

	add_long("The small path you are on twists its way through " +
        "the trees from the north to the southeast. ",
        ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

add_mirkwood_exits(([
        "southwest" : "r04/f07",
        "south" : "r04/f08",
        "northwest" : "r02/f07",
        "east" : "r03/f09",
        "northeast" : "r02/f09",
        "west" : "r03/f07",
    ]));

    add_exit(WOODSMEN_DIR + "weanting1", "southeast");
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r02/p08-r02", "north");
    
}

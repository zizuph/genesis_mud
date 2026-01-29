#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "path";

void create_mirkwood_south_forest_path_room() {

    add_long("The small path you are on twists its way through " +
        "the trees from the north to the southwest. ",
        ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

    add_mirkwood_exits(([
        "southeast" : "r02/f10",
        "south" : "r02/f09",
        "northwest" : "r00/f08",
        "east" : "r01/f10",
        "northeast" : "r00/f10",
        "west" : "r01/f08",
    ]));
    
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r02/p08-r02", "southwest");
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r00/p09-r00", "north");
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "path";

void create_mirkwood_south_forest_path_room() {

     add_long("The small path you are on twists its way through " +
        "the trees from the north to the south. ",
        ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_OLDROAD_DIR + "r03",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r05",

        "southeast" : "r01/f10",
        "southwest" : "r01/f08",
        "east" : "r00/f10",
        "west" : "r00/f08",
    ]));

    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r01/p09-r01", "south");
    add_exit(MIRKWOOD_OLDROAD_DIR + "r04", "north");    
}

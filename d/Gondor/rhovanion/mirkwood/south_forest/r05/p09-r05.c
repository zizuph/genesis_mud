#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "path";

void create_mirkwood_south_forest_path_room() {

	add_long("The small path you are on twists its way through " +
        "the trees from the north to the south. ",
        ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

add_mirkwood_exits(([
        "southeast" : "r06/f10",
        "southwest" : "r06/f08",
        "northwest" : "r04/f08",
        "east" : "r05/f10",
        "northeast" : "r04/f10",
        "west" : "r05/f08",
    ]));
    
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r06/p09-r06", "south");
    add_exit(WOODSMEN_DIR + "weanting1", "north");
}

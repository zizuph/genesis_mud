#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "path";

void create_mirkwood_south_forest_path_room() {

    add_long("The small path you are on twists its way through " +
        "the trees from the north to the south. ",
        ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

    add_mirkwood_exits(([
        "southeast" : "r07/f10",
        "southwest" : "r07/f08",
        "northwest" : "r05/f08",
        "east" : "r06/f10",
        "northeast" : "r05/f10",
        "west" : "r06/f08",
    ]));

    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r07/p09-r07", "south");
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r05/p09-r05", "north");
}

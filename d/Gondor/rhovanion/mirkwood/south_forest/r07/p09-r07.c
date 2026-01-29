#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "path";

void create_mirkwood_south_forest_path_room() {

    add_long("The small path you are on twists its way through " +
        "the trees from the north to the southwest. ",
        ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

    add_mirkwood_exits(([
        "southeast" : "r08/f10",
        "south" : "r08/f09",
        "northwest" : "r06/f08",
        "east" : "r07/f10",
        "northeast" : "r06/f10",
        "west" : "r07/f08",
    ]));
    
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r08/p08-r08", "southwest");
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r06/p09-r06", "north");
}

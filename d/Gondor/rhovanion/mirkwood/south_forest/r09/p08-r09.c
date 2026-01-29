#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "path";

void create_mirkwood_south_forest_path_room() {

    add_long("The small path you are on twists its way through " +
        "the trees from the north to the south. ",
        ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

    add_mirkwood_exits(([
        "southeast" : "r10/f09",
        "southwest" : "r10/f07",
        "northwest" : "r08/f07",
        "east" : "r09/f09",
        "northeast" : "r08/f09",
        "west" : "r09/f07",
    ]));

    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r10/p08-r10", "south");
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r08/p08-r08", "north");
}

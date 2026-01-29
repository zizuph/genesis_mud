#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "path";

void create_mirkwood_south_forest_path_room() {

    add_long("The small path you are on twists its way through " +
        "the trees from the north to the south. ",
        ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

    add_mirkwood_exits(([
        "southeast" : "r10/f09",
        "southwest" : "r10/f07",
        "south" : "r10/p08",
        "northwest" : "r08/f07",
        "east" : "r09/f09",
        "north" : "r08/p08",
        "northeast" : "r08/f09",
        "west" : "r09/f07",
    ]));
    
}

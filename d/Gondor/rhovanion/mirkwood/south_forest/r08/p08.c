#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "path";

void create_mirkwood_south_forest_path_room() {

    add_long("The small path you are on twists its way through " +
        "the trees from the northeast to the south. ",
        ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

    add_mirkwood_exits(([
        "southeast" : "r09/f09",
        "southwest" : "r09/f07",
        "south" : "r09/p08",
        "northwest" : "r07/f07",
        "east" : "r08/f09",
        "north" : "r07/f08",
        "northeast" : "r07/p09",
        "west" : "r08/f07",
    ]));
    
}

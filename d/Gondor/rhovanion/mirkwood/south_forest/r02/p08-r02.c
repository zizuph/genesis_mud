#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "path";

void create_mirkwood_south_forest_path_room() {

	add_long("The small path you are on twists its way through " +
        "the trees from the northeast to the south. ",
        ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

add_mirkwood_exits(([
        "southeast" : "r03/f09",
        "southwest" : "r03/f07",
        "northwest" : "r01/f07",
        "east" : "r02/f09",
        "north" : "r01/f08",
        "west" : "r02/f07",
    ]));
    
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r03/p08-r03", "south");
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r01/p09-r01", "northeast");
}

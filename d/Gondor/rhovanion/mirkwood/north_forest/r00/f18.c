#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "west"      : MIRKWOOD_ELFPATH_DIR + "p17",
        "south"     : MIRKWOOD_ELFPATH_DIR + "p18",
        "southeast" : MIRKWOOD_ELFPATH_DIR + "p19",
        "southwest" : MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f17",

        "northwest" : "r01/f17",
        "east" : "r00/f19",
        "north" : "r01/f18",
        "northeast" : "r01/f19",
    ]));
    
}

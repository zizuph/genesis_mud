#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_ELFPATH_DIR + "p14",
        "south"     : MIRKWOOD_ELFPATH_DIR + "p15",
        "southeast" : MIRKWOOD_ELFPATH_DIR + "p16",
        
        "northwest" : "r02/f14",
        "east" : "r01/f16",
        "north" : "r02/f15",
        "northeast" : "r02/f16",
        "west" : "r01/f14",
    ]));
    
}

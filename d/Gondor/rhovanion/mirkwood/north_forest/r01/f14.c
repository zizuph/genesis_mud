#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_ELFPATH_DIR + "p13",
        "south"     : MIRKWOOD_ELFPATH_DIR + "p14",
        "southeast" : MIRKWOOD_ELFPATH_DIR + "p15",
        
        "northwest" : "r02/f13",
        "east" : "r01/f15",
        "north" : "r02/f14",
        "northeast" : "r02/f15",
        "west" : "r01/f13",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_ELFPATH_DIR + "p15",
        "south"     : MIRKWOOD_ELFPATH_DIR + "p16",
        "southeast" : MIRKWOOD_ELFPATH_DIR + "p17",
        
        "northwest" : "r02/f15",
        "east" : "r01/f17",
        "north" : "r02/f16",
        "northeast" : "r02/f17",
        "west" : "r01/f15",
    ]));
    
}

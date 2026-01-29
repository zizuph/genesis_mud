#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p15",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p16",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p17",
        
        "southeast" : "r16/f17",
        "southwest" : "r16/f15",
        "south" : "r16/f16",
        "east" : "r17/f17",
        "west" : "r17/f15",
    ]));
    
}

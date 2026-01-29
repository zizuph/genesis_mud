#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r10",
        "south" : MIRKWOOD_OLDROAD_DIR + "r11",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r12",
        
        "northwest" : "r01/f15",
        "east" : "r00/f17",
        "north" : "r01/f16",
        "northeast" : "r01/f17",
        "west" : "r00/f15",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r08",
        "south" : MIRKWOOD_OLDROAD_DIR + "r09",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r10",
        
        "northwest" : "r01/f13",
        "east" : "r00/f15",
        "north" : "r01/f14",
        "northeast" : "r01/f15",
        "west" : "r00/f13",
    ]));
    
}

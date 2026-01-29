#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r09",
        "south" : MIRKWOOD_OLDROAD_DIR + "r10",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r11",
        
        "northwest" : "r01/f14",
        "east" : "r00/f16",
        "north" : "r01/f15",
        "northeast" : "r01/f16",
        "west" : "r00/f14",
    ]));
    
}

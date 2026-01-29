#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "south" : MIRKWOOD_ELFPATH_DIR + "p01",
        "southeast" : MIRKWOOD_ELFPATH_DIR + "p02",
        
        "east" : "r01/f02",
        "north" : "r02/f01",
        "northeast" : "r02/f02",
    ]));
    
}

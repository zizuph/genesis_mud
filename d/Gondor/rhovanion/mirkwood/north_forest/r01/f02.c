#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_ELFPATH_DIR + "p01",
        "south"     : MIRKWOOD_ELFPATH_DIR + "p02",
        "southeast" : MIRKWOOD_ELFPATH_DIR + "p03",
        
        "northwest" : "r02/f01",
        "east" : "r01/f03",
        "north" : "r02/f02",
        "northeast" : "r02/f03",
        "west" : "r01/f01",
    ]));
    
}

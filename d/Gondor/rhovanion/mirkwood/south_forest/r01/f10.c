#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r02/f11",
        "southwest" : "r02/f09",
        "south" : "r02/f10",
        "northwest" : "r00/p09-r00",
        "east" : "r01/f11",
        "north" : "r00/f10",
        "northeast" : "r00/f11",
        "west" : "r01/p09-r01",
    ]));
    
}

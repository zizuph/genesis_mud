#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r03/f11",
        "southwest" : "r03/f09",
        "south" : "r03/f10",
        "northwest" : "r01/p09-r01",
        "east" : "r02/f11",
        "north" : "r01/f10",
        "northeast" : "r01/f11",
        "west" : "r02/f09",
    ]));
    
}

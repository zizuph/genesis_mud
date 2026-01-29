#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r03/f50",
        "south" : "r03/f51",
        "northwest" : "r01/f50",
        "north" : "r01/f51",
        "west" : "r02/f50",
    ]));
    
}

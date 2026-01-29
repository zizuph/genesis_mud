#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r03/f10",
        "southwest" : "r03/p08-r03",
        "south" : "r03/f09",
        "northwest" : "r01/f08",
        "east" : "r02/f10",
        "north" : "r01/p09-r01",
        "northeast" : "r01/f10",
        "west" : "r02/p08-r02",
    ]));
    
}

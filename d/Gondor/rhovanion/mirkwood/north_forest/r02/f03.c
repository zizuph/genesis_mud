#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r01/f04",
        "southwest" : "r01/f02",
        "south" : "r01/f03",
        "northwest" : "r03/f02",
        "east" : "r02/f04",
        "north" : "r03/f03",
        "northeast" : "r03/f04",
        "west" : "r02/f02",
    ]));
    
}

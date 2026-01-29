#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r01/f03",
        "southwest" : "r01/f01",
        "south" : "r01/f02",
        "northwest" : "r03/f01",
        "east" : "r02/f03",
        "north" : "r03/f02",
        "northeast" : "r03/f03",
        "west" : "r02/f01",
    ]));
    
}

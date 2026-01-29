#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r01/f05",
        "southwest" : "r01/f03",
        "south" : "r01/f04",
        "northwest" : "r03/f03",
        "east" : "r02/f05",
        "north" : "r03/f04",
        "northeast" : "r03/f05",
        "west" : "r02/f03",
    ]));
    
}

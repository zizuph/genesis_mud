#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r01/f06",
        "southwest" : "r01/f04",
        "south" : "r01/f05",
        "northwest" : "r03/f04",
        "east" : "r02/f06",
        "north" : "r03/f05",
        "northeast" : "r03/f06",
        "west" : "r02/f04",
    ]));
    
}

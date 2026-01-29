#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r01/f10",
        "southwest" : "r01/f08",
        "south" : "r01/f09",
        "northwest" : "r03/f08",
        "east" : "r02/f10",
        "north" : "r03/f09",
        "northeast" : "r03/f10",
        "west" : "r02/f08",
    ]));
    
}

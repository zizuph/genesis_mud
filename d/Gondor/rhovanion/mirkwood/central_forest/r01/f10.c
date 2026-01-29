#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r00/f11",
        "southwest" : "r00/f09",
        "south" : "r00/f10",
        "northwest" : "r02/f09",
        "east" : "r01/f11",
        "north" : "r02/f10",
        "northeast" : "r02/f11",
        "west" : "r01/f09",
    ]));
    
}

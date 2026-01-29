#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r00/f52",
        "southwest" : "r00/f50",
        "south" : "r00/f51",
        "northwest" : "r02/f50",
        "north" : "r02/f51",
        "west" : "r01/f50",
    ]));
    
}

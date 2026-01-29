#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r04/f50",
        "south" : "r04/f51",
        "northwest" : "r06/f50",
        "north" : "r06/f51",
        "west" : "r05/f50",
    ]));
    
}

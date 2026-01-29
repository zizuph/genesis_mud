#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r10/f43",
        "southwest" : "r10/f41",
        "south" : "r10/f42",
        "northwest" : "r12/f41",
        "west" : "r11/f41",
    ]));
    
}

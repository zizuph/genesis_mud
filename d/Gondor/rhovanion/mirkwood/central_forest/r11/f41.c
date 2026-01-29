#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r10/f42",
        "southwest" : "r10/f40",
        "south" : "r10/f41",
        "northwest" : "r12/f40",
        "east" : "r11/f42",
        "north" : "r12/f41",
        "west" : "r11/f40",
    ]));
    
}

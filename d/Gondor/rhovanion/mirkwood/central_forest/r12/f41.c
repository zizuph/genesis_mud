#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r11/f42",
        "southwest" : "r11/f40",
        "south" : "r11/f41",
        "northwest" : "r13/f40",
        "west" : "r12/f40",
    ]));
    
}

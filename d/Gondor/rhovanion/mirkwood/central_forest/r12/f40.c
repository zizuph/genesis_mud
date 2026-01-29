#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r11/f41",
        "southwest" : "r11/f39",
        "south" : "r11/f40",
        "northwest" : "r13/f39",
        "east" : "r12/f41",
        "north" : "r13/f40",
        "west" : "r12/f39",
    ]));
    
}

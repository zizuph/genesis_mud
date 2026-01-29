#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r11/f34",
        "southwest" : "r11/f32",
        "south" : "r11/f33",
        "northwest" : "r13/f32",
        "north" : "r13/f33",
        "west" : "r12/f32",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r10/f34",
        "southwest" : "r10/f32",
        "south" : "r10/f33",
        "northwest" : "r12/f32",
        "east" : "r11/f34",
        "north" : "r12/f33",
        "west" : "r11/f32",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r15/f33",
        "southwest" : "r15/f31",
        "south" : "r15/f32",
        "northwest" : "r17/f31",
        "east" : "r16/f33",
        "north" : "r17/f32",
        "west" : "r16/f31",
    ]));
    
}

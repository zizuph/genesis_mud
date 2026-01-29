#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r14/f33",
        "southwest" : "r14/f31",
        "south" : "r14/f32",
        "northwest" : "r16/f31",
        "east" : "r15/f33",
        "north" : "r16/f32",
        "northeast" : "r16/f33",
        "west" : "r15/f31",
    ]));
    
}

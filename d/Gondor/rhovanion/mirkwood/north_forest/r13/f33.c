#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r12/f32",
        "south" : "r12/f33",
        "northwest" : "r14/f32",
        "north" : "r14/f33",
        "west" : "r13/f32",
    ]));
    
}

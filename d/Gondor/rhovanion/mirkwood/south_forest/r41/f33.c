#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "northwest" : "r40/f32",
        "north" : "r40/f33",
        "northeast" : "r40/f34",
        "west" : "r41/f32",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : "r42/f30",
        "south" : "r42/f31",
        "northwest" : "r40/f30",
        "east" : "r41/f32",
        "north" : "r40/f31",
        "northeast" : "r40/f32",
        "west" : "r41/f30",
    ]));
    
}

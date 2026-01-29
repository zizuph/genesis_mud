#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : "r41/f32",
        "south" : "r41/f33",
        "northwest" : "r39/f32",
        "east" : "r40/f34",
        "north" : "r39/f33",
        "northeast" : "r39/f34",
        "west" : "r40/f32",
    ]));
    
}

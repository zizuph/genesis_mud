#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r43/f30",
        "northwest" : "r41/f30",
        "north" : "r41/f31",
        "northeast" : "r41/f32",
        "west" : "r42/f30",
    ]));
    
}

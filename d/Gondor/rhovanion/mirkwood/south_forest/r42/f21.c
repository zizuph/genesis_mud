#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r43/f22",
        "northwest" : "r41/f20",
        "east" : "r42/f22",
        "north" : "r41/f21",
        "northeast" : "r41/f22",
        "west" : "r42/f20",
    ]));
    
}

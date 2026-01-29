#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "northwest" : "r40/f17",
        "east" : "r41/f19",
        "north" : "r40/f18",
        "northeast" : "r40/f19",
        "west" : "r41/f17",
    ]));
    
}

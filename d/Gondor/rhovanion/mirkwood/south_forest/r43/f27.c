#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "northwest" : "r42/f26",
        "east" : "r43/f28",
        "north" : "r42/f27",
        "northeast" : "r42/f28",
        "west" : "r43/f26",
    ]));
    
}

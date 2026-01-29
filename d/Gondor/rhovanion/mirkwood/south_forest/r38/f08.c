#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "northwest" : "r37/f07",
        "east" : "r38/p09",
        "north" : "r37/f08",
        "northeast" : "r37/f09",
        "west" : "r38/f07",
    ]));
    
}

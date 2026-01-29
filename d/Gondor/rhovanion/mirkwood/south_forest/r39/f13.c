#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r40/f14",
        "northwest" : "r38/f12",
        "east" : "r39/f14",
        "north" : "r38/f13",
        "northeast" : "r38/f14",
        "west" : "r39/f12",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r40/f15",
        "south" : "r40/f14",
        "northwest" : "r38/f13",
        "east" : "r39/f15",
        "north" : "r38/f14",
        "northeast" : "r38/f15",
        "west" : "r39/f13",
    ]));
    
}

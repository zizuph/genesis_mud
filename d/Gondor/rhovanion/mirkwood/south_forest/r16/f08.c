#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r17/f09",
        "south" : "r17/f08",
        "east" : "r16/f09",
        "north" : "r15/f08",
        "northeast" : "r15/f09",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r16/f09",
        "south" : "r16/f08",
        "northwest" : "r14/f07",
        "east" : "r15/f09",
        "north" : "r14/f08",
        "northeast" : "r14/f09",
    ]));
    
}

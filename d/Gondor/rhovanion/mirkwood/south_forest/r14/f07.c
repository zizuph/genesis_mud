#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r15/f08",
        "northwest" : "r13/f06",
        "east" : "r14/f08",
        "north" : "r13/f07",
        "northeast" : "r13/f08",
    ]));
    
}

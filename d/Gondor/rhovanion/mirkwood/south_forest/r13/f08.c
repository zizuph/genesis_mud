#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r14/f09",
        "southwest" : "r14/f07",
        "south" : "r14/f08",
        "northwest" : "r12/f07",
        "east" : "r13/f09",
        "north" : "r12/f08",
        "northeast" : "r12/f09",
        "west" : "r13/f07",
    ]));
    
}

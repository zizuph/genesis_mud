#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r14/f08",
        "south" : "r14/f07",
        "northwest" : "r12/f06",
        "east" : "r13/f08",
        "north" : "r12/f07",
        "northeast" : "r12/f08",
        "west" : "r13/f06",
    ]));
    
}

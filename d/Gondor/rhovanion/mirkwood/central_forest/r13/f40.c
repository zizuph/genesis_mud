#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r12/f41",
        "southwest" : "r12/f39",
        "south" : "r12/f40",
        "northwest" : "r14/f39",
        "north" : "r14/f40",
        "west" : "r13/f39",
    ]));
    
}

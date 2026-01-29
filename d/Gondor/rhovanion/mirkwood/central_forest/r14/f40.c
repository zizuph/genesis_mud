#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r13/f39",
        "south" : "r13/f40",
        "northwest" : "r15/f39",
        "north" : "r15/f40",
        "west" : "r14/f39",
    ]));
    
}

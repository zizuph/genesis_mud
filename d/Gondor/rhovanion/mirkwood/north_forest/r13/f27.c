#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r12/f28",
        "southwest" : "r12/f26",
        "south" : "r12/f27",
        "northwest" : "r14/f26",
        "east" : "r13/f28",
        "north" : "r14/f27",
        "northeast" : "r14/f28",
        "west" : "r13/f26",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(24);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r12/f26",
        "southwest" : "r12/f24",
        "south" : "r12/f25",
        "northwest" : "r14/f24",
        "east" : "r13/f26",
        "north" : "r14/f25",
        "northeast" : "r14/f26",
        "west" : "r13/f24",
    ]));
    
}

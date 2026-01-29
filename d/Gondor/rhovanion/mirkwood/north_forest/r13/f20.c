#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(21);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r12/f21",
        "southwest" : "r12/f19",
        "south" : "r12/f20",
        "northwest" : "r14/f19",
        "east" : "r13/f21",
        "north" : "r14/f20",
        "northeast" : "r14/f21",
        "west" : "r13/f19",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(12);
    add_mirkwood_exits(([
        "southeast" : "r14/f19",
        "southwest" : "r14/f17",
        "south" : "r14/f18",
        "northwest" : "r12/f17",
        "east" : "r13/f19",
        "north" : "r12/f18",
        "northeast" : "r12/f19",
        "west" : "r13/f17",
    ]));
    
}

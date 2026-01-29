#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r14/f18",
        "southwest" : "r14/f16",
        "south" : "r14/f17",
        "northwest" : "r12/f16",
        "east" : "r13/f18",
        "north" : "r12/f17",
        "northeast" : "r12/f18",
        "west" : "r13/f16",
    ]));
    
}

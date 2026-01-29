#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(97);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r12/f20",
        "southwest" : "r12/f18",
        "south" : "r12/f19",
        "northwest" : "r14/f18",
        "east" : "r13/f20",
        "north" : "r14/f19",
        "northeast" : "r13/f20",
        "west" : "r13/f18",
    ]));
    
}

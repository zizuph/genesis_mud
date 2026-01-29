#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(23);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r12/f30",
        "southwest" : "r12/f28",
        "south" : "r12/f29",
        "northwest" : "r14/f28",
        "east" : "r13/f30",
        "north" : "r14/f29",
        "northeast" : "r14/f30",
        "west" : "r13/f28",
    ]));
    
}

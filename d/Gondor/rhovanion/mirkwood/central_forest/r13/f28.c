#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(22);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r12/f29",
        "southwest" : "r12/f27",
        "south" : "r12/f28",
        "northwest" : "r14/f27",
        "east" : "r13/f29",
        "north" : "r14/f28",
        "northeast" : "r14/f29",
        "west" : "r13/f27",
    ]));
    
}

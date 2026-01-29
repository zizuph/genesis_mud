#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(25);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r12/f31",
        "southwest" : "r12/f29",
        "south" : "r12/f30",
        "northwest" : "r14/f29",
        "east" : "r13/f31",
        "north" : "r14/f30",
        "northeast" : "r14/f31",
        "west" : "r13/f29",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r12/f39",
        "southwest" : "r12/f37",
        "south" : "r12/f38",
        "northwest" : "r14/f37",
        "east" : "r13/f39",
        "north" : "r14/f38",
        "northeast" : "r14/f39",
        "west" : "r13/f37",
    ]));
    
}

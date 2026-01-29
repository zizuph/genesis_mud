#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r12/f13",
        "southwest" : "r12/f11",
        "south" : "r12/f12",
        "northwest" : "r14/f11",
        "east" : "r13/f13",
        "north" : "r14/f12",
        "northeast" : "r14/f13",
        "west" : "r13/f11",
    ]));
    
}

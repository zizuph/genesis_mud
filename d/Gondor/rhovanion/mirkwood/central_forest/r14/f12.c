#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r13/f13",
        "southwest" : "r13/f11",
        "south" : "r13/f12",
        "northwest" : "r15/f11",
        "east" : "r14/f13",
        "north" : "r15/f12",
        "northeast" : "r15/f13",
        "west" : "r14/f11",
    ]));
    
}

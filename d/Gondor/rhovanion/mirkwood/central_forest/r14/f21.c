#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(71);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r13/f22",
        "southwest" : "r13/f21",
        "south" : "r13/f21",
        "northwest" : "r15/f20",
        "east" : "r14/f22",
        "north" : "r15/f21",
        "northeast" : "r15/f22",
        "west" : "r14/f20",
    ]));
    
}

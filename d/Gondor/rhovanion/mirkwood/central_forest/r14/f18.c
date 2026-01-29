#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(87);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r13/f19",
        "southwest" : "r13/f17",
        "south" : "r13/f18",
        "northwest" : "r15/f17",
        "east" : "r14/f19",
        "north" : "r15/f18",
        "northeast" : "r14/f19",
        "west" : "r14/f17",
    ]));
    
}

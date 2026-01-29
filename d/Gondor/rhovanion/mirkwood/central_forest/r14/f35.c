#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r13/f36",
        "southwest" : "r13/f34",
        "south" : "r13/f35",
        "northwest" : "r15/f34",
        "east" : "r14/f36",
        "north" : "r15/f35",
        "northeast" : "r15/f36",
        "west" : "r14/f34",
    ]));
    
}

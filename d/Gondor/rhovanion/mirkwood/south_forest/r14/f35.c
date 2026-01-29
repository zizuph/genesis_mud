#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r15/f36",
        "southwest" : "r15/f34",
        "south" : "r15/f35",
        "northwest" : "r13/f34",
        "east" : "r14/f36",
        "north" : "r13/f35",
        "northeast" : "r13/f36",
        "west" : "r14/f34",
    ]));
    
}

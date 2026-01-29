#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r14/f37",
        "southwest" : "r14/f35",
        "south" : "r14/f36",
        "northwest" : "r12/f35",
        "east" : "r13/f37",
        "north" : "r12/f36",
        "northeast" : "r12/f37",
        "west" : "r13/f35",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r13/f37",
        "southwest" : "r13/f35",
        "south" : "r13/f36",
        "northwest" : "r15/f35",
        "east" : "r14/f37",
        "north" : "r15/f36",
        "northeast" : "r15/f37",
        "west" : "r14/f35",
    ]));
    
}

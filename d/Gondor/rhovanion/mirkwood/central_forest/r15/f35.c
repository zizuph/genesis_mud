#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r14/f36",
        "southwest" : "r14/f34",
        "south" : "r14/f35",
        "northwest" : "r16/f34",
        "east" : "r15/f36",
        "north" : "r16/f35",
        "northeast" : "r16/f36",
        "west" : "r15/f34",
    ]));
    
}

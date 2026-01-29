#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r15/f36",
        "southwest" : "r15/f34",
        "south" : "r15/f35",
        "northwest" : "r17/f34",
        "east" : "r16/f36",
        "north" : "r17/f35",
        "northeast" : "r17/f36",
        "west" : "r16/f34",
    ]));
    
}

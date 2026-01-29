#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(66);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r08/m36",
        "southwest" : "r08/f34",
        "south" : "r08/m35",
        "northwest" : "r10/f34",
        "east" : "r09/f36",
        "north" : "r10/f35",
        "northeast" : "r10/f36",
        "west" : "r09/f34",
    ]));
    
}

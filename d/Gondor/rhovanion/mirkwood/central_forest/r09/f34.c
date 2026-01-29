#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(61);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r08/m35",
        "southwest" : "r08/f33",
        "south" : "r08/f34",
        "northwest" : "r10/f33",
        "east" : "r09/f35",
        "north" : "r10/f34",
        "northeast" : "r10/f35",
        "west" : "r09/f33",
    ]));
    
}

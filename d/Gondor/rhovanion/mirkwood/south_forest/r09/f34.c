#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r10/f35",
        "southwest" : "r10/f33",
        "south" : "r10/f34",
        "northwest" : "r08/f33",
        "east" : "r09/f35",
        "north" : "r08/f34",
        "northeast" : "r08/f35",
        "west" : "r09/f33",
    ]));
    
}

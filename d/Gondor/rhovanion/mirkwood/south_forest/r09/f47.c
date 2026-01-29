#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r10/f48",
        "southwest" : "r10/f46",
        "south" : "r10/f47",
        "northwest" : "r08/f46",
        "east" : "r09/f48",
        "north" : "r08/f47",
        "northeast" : "r08/f48",
        "west" : "r09/f46",
    ]));
    
}

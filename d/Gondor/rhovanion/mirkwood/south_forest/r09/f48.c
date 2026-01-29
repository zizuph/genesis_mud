#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r10/f49",
        "southwest" : "r10/f47",
        "south" : "r10/f48",
        "northwest" : "r08/f47",
        "east" : "r09/f49",
        "north" : "r08/f48",
        "northeast" : "r08/f49",
        "west" : "r09/f47",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r10/f11",
        "southwest" : "r10/f09",
        "south" : "r10/f10",
        "northwest" : "r08/f09",
        "east" : "r09/f11",
        "north" : "r08/f10",
        "northeast" : "r08/f11",
        "west" : "r09/f09",
    ]));
    
}

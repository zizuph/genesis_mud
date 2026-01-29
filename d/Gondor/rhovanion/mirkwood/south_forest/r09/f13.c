#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r10/f14",
        "southwest" : "r10/f12",
        "south" : "r10/f13",
        "northwest" : "r08/f12",
        "east" : "r09/f14",
        "north" : "r08/f13",
        "northeast" : "r08/f14",
        "west" : "r09/f12",
    ]));
    
}

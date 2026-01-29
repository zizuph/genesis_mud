#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(56);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f22",
        "southwest" : "r08/f20",
        "south" : "r08/f21",
        "northwest" : "r10/f20",
        "east" : "r09/f22",
        "north" : "r10/f21",
        "northeast" : "r10/f22",
        "west" : "r09/f20",
    ]));
    
}

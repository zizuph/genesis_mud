#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(48);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f21",
        "southwest" : "r08/f19",
        "south" : "r08/f20",
        "northwest" : "r10/f19",
        "east" : "r09/f21",
        "north" : "r10/f20",
        "northeast" : "r10/f21",
        "west" : "r09/f19",
    ]));
    
}

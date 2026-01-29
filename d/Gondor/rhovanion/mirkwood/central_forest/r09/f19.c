#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(40);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f20",
        "southwest" : "r08/f18",
        "south" : "r08/f19",
        "northwest" : "r10/f18",
        "east" : "r09/f20",
        "north" : "r10/f19",
        "northeast" : "r10/f20",
        "west" : "r09/f18",
    ]));
    
}

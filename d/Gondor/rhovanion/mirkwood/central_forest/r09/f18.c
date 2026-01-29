#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(29);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f19",
        "southwest" : "r08/f17",
        "south" : "r08/f18",
        "northwest" : "r10/f17",
        "east" : "r09/f19",
        "north" : "r10/f18",
        "northeast" : "r10/f19",
        "west" : "r09/f17",
    ]));
    
}

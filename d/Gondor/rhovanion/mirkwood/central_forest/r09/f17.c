#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(28);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r08/f18",
        "southwest" : "r08/f16",
        "south" : "r08/f17",
        "northwest" : "r10/f16",
        "east" : "r09/f18",
        "north" : "r10/f17",
        "northeast" : "r10/f18",
        "west" : "r09/f16",
    ]));
    
}

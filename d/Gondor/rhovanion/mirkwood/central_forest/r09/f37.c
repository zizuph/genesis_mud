#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(64);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r08/m38",
        "southwest" : "r08/m36",
        "south" : "r08/m37",
        "northwest" : "r10/f36",
        "east" : "r09/f38",
        "north" : "r10/f37",
        "northeast" : "r10/f38",
        "west" : "r09/f36",
    ]));
    
}

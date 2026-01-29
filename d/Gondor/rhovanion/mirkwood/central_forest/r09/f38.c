#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(56);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r08/f39",
        "southwest" : "r08/m37",
        "south" : "r08/m38",
        "northwest" : "r10/f37",
        "east" : "r09/f39",
        "north" : "r10/f38",
        "northeast" : "r10/f39",
        "west" : "r09/f37",
    ]));
    
}

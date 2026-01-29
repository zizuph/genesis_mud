#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(54);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r08/f40",
        "southwest" : "r08/m38",
        "south" : "r08/f39",
        "northwest" : "r10/f38",
        "east" : "r09/f40",
        "north" : "r10/f39",
        "northeast" : "r10/f40",
        "west" : "r09/f38",
    ]));
    
}

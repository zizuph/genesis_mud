#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r08/f43",
        "southwest" : "r08/f41",
        "south" : "r08/f42",
        "northwest" : "r10/f41",
        "east" : "r09/f43",
        "north" : "r10/f42",
        "northeast" : "r10/f43",
        "west" : "r09/f41",
    ]));
    
}

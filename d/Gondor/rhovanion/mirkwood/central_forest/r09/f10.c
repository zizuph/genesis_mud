#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r08/f11",
        "southwest" : "r08/f09",
        "south" : "r08/f10",
        "northwest" : "r10/f09",
        "east" : "r09/f11",
        "north" : "r10/f10",
        "northeast" : "r10/f11",
        "west" : "r09/f09",
    ]));
    
}

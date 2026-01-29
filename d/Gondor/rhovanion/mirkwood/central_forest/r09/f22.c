#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(68);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f23",
        "southwest" : "r08/f21",
        "south" : "r08/f22",
        "northwest" : "r10/f21",
        "east" : "r09/f23",
        "north" : "r10/f22",
        "northeast" : "r10/f23",
        "west" : "r09/f21",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(51);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r08/f29",
        "southwest" : "r08/f27",
        "south" : "r08/f28",
        "northwest" : "r10/f27",
        "east" : "r09/f29",
        "north" : "r10/f28",
        "northeast" : "r10/f29",
        "west" : "r09/f27",
    ]));
    
}

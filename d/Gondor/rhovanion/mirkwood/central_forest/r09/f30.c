#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(43);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r08/f31",
        "southwest" : "r08/f29",
        "south" : "r08/f30",
        "northwest" : "r10/f29",
        "east" : "r09/f31",
        "north" : "r10/f30",
        "northeast" : "r10/f31",
        "west" : "r09/f29",
    ]));
    
}

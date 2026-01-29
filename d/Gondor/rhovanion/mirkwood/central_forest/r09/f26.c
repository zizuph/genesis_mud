#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(44);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r08/f27",
        "southwest" : "r08/f26",
        "south" : "r08/f26",
        "northwest" : "r10/f25",
        "east" : "r09/f27",
        "north" : "r10/f26",
        "northeast" : "r10/f27",
        "west" : "r09/f25",
    ]));
    
}

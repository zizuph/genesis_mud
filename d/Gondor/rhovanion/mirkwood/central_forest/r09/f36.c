#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(62);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r08/m37",
        "southwest" : "r08/m35",
        "south" : "r08/m36",
        "northwest" : "r10/f35",
        "east" : "r09/f37",
        "north" : "r10/f36",
        "northeast" : "r10/f37",
        "west" : "r09/f35",
    ]));
    
}

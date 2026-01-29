#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r07/f48",
        "southwest" : "r07/f46",
        "south" : "r07/f47",
        "northwest" : "r09/f46",
        "east" : "r08/f48",
        "north" : "r09/f47",
        "northeast" : "r09/f48",
        "west" : "r08/f46",
    ]));
    
}

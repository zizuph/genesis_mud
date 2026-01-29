#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r06/f48",
        "southwest" : "r06/f46",
        "south" : "r06/f47",
        "northwest" : "r08/f46",
        "east" : "r07/f48",
        "north" : "r08/f47",
        "northeast" : "r08/f48",
        "west" : "r07/f46",
    ]));
    
}

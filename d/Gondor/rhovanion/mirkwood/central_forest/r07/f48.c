#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r06/f49",
        "southwest" : "r06/f47",
        "south" : "r06/f48",
        "northwest" : "r08/f47",
        "east" : "r07/f49",
        "north" : "r08/f48",
        "northeast" : "r08/f49",
        "west" : "r07/f47",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(60);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r06/m36",
        "southwest" : "r06/m34",
        "south" : "r06/m35",
        "northwest" : "r08/f34",
        "east" : "r07/m36",
        "north" : "r08/m35",
        "northeast" : "r08/m36",
        "west" : "r07/f34",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(65);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r06/m35",
        "southwest" : "r06/m33",
        "south" : "r06/m34",
        "northwest" : "r08/f33",
        "east" : "r07/f35",
        "north" : "r08/f34",
        "northeast" : "r08/m35",
        "west" : "r07/f33",
    ]));
    
}

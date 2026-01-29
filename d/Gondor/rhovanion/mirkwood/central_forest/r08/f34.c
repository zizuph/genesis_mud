#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(73);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r07/f35",
        "southwest" : "r07/f33",
        "south" : "r07/f34",
        "northwest" : "r09/f33",
        "east" : "r08/m35",
        "north" : "r09/f34",
        "northeast" : "r09/f35",
        "west" : "r08/f33",
    ]));
    
}

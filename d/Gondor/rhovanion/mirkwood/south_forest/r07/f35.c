#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(35);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f36",
        "southwest" : "r08/f34",
        "south" : "r08/f35",
        "northwest" : "r06/f34",
        "east" : "r07/f36",
        "north" : "r06/f35",
        "northeast" : "r06/f36",
        "west" : "r07/f34",
    ]));
    
}

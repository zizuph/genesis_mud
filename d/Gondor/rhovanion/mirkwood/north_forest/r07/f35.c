#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r06/f36",
        "southwest" : "r06/f34",
        "south" : "r06/f35",
        "northwest" : "r08/f34",
        "east" : "r07/f36",
        "north" : "r08/f35",
        "northeast" : "r08/f36",
        "west" : "r07/f34",
    ]));
    
}

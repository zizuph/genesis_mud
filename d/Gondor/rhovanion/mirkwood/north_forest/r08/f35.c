#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r07/f36",
        "southwest" : "r07/f34",
        "south" : "r07/f35",
        "northwest" : "r09/f34",
        "east" : "r08/f36",
        "north" : "r09/f35",
        "northeast" : "r09/f36",
        "west" : "r08/f34",
    ]));
    
}

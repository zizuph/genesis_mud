#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r05/f36",
        "southwest" : "r05/f34",
        "south" : "r05/f35",
        "northwest" : "r07/f34",
        "east" : "r06/f36",
        "north" : "r07/f35",
        "northeast" : "r07/f36",
        "west" : "r06/f34",
    ]));
    
}

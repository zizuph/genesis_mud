#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(63);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f36",
        "southwest" : "r07/f34",
        "south" : "r07/f35",
        "northwest" : "r05/f34",
        "east" : "r06/f36",
        "north" : "r05/f35",
        "northeast" : "r05/f36",
        "west" : "r06/f34",
    ]));
    
}

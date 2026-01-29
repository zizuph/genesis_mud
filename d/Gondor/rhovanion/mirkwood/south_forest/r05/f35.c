#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(30);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f36",
        "southwest" : "r06/f34",
        "south" : "r06/f35",
        "northwest" : "r04/f34",
        "east" : "r05/f36",
        "north" : "r04/f35",
        "northeast" : "r04/f36",
        "west" : "r05/f34",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f36",
        "southwest" : "r04/f34",
        "south" : "r04/f35",
        "northwest" : "r02/f34",
        "east" : "r03/f36",
        "north" : "r02/f35",
        "northeast" : "r02/f36",
        "west" : "r03/f34",
    ]));
    
}

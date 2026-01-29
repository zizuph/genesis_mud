#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r03/f36",
        "southwest" : "r03/f34",
        "south" : "r03/f35",
        "northwest" : "r01/f34",
        "east" : "r02/f36",
        "north" : "r01/f35",
        "northeast" : "r01/f36",
        "west" : "r02/f34",
    ]));
    
}

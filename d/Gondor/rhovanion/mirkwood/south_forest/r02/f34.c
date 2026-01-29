#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r03/f35",
        "southwest" : "r03/f33",
        "south" : "r03/f34",
        "northwest" : "r01/f33",
        "east" : "r02/f35",
        "north" : "r01/f34",
        "northeast" : "r01/f35",
        "west" : "r02/f33",
    ]));
    
}

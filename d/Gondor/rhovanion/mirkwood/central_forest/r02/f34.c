#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(62);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f35",
        "southwest" : "r01/f33",
        "south" : "r01/f34",
        "northwest" : "r03/f33",
        "east" : "r02/f35",
        "north" : "r03/f34",
        "northeast" : "r03/m35",
        "west" : "r02/f33",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(89);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f35",
        "southwest" : "r02/f33",
        "south" : "r02/f34",
        "northwest" : "r04/m33",
        "east" : "r03/m35",
        "north" : "r04/m34",
        "northeast" : "r04/m35",
        "west" : "r03/f33",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f48",
        "southwest" : "r02/f46",
        "south" : "r02/f47",
        "northwest" : "r04/f46",
        "east" : "r03/f48",
        "north" : "r04/f47",
        "northeast" : "r04/f48",
        "west" : "r03/f46",
    ]));
    
}

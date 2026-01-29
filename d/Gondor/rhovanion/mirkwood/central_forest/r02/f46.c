#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f47",
        "southwest" : "r01/f45",
        "south" : "r01/f46",
        "northwest" : "r03/f45",
        "east" : "r02/f47",
        "north" : "r03/f46",
        "northeast" : "r03/f47",
        "west" : "r02/f45",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(51);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f26",
        "southwest" : "r01/f24",
        "south" : "r01/f25",
        "northwest" : "r03/f24",
        "east" : "r02/f26",
        "north" : "r03/f25",
        "northeast" : "r03/f26",
        "west" : "r02/f24",
    ]));
    
}

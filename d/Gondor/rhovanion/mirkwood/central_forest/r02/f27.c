#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(52);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f28",
        "southwest" : "r01/f26",
        "south" : "r01/f27",
        "northwest" : "r03/f26",
        "east" : "r02/f28",
        "north" : "r03/f27",
        "northeast" : "r03/f28",
        "west" : "r02/f26",
    ]));
    
}

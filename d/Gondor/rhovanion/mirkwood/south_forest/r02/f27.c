#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r03/f28",
        "southwest" : "r03/f26",
        "south" : "r03/f27",
        "northwest" : "r01/f26",
        "east" : "r02/f28",
        "north" : "r01/f27",
        "northeast" : "r01/f28",
        "west" : "r02/f26",
    ]));
    
}

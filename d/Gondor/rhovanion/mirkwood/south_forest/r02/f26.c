#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r03/f27",
        "southwest" : "r03/f25",
        "south" : "r03/f26",
        "northwest" : "r01/f25",
        "east" : "r02/f27",
        "north" : "r01/f26",
        "northeast" : "r01/f27",
        "west" : "r02/f25",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r03/f26",
        "southwest" : "r03/f24",
        "south" : "r03/f25",
        "northwest" : "r01/f24",
        "east" : "r02/f26",
        "north" : "r01/f25",
        "northeast" : "r01/f26",
        "west" : "r02/f24",
    ]));
    
}

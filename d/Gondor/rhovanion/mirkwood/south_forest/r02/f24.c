#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r03/f25",
        "southwest" : "r03/f23",
        "south" : "r03/f24",
        "northwest" : "r01/f23",
        "east" : "r02/f25",
        "north" : "r01/f24",
        "northeast" : "r01/f25",
        "west" : "r02/f23",
    ]));
    
}

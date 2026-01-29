#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r03/f50",
        "southwest" : "r03/f48",
        "south" : "r03/f49",
        "northwest" : "r01/f48",
        "east" : "r02/f50",
        "north" : "r01/f49",
        "northeast" : "r01/f50",
        "west" : "r02/f48",
    ]));
    
}

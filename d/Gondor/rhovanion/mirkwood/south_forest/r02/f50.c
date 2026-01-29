#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r03/f51",
        "southwest" : "r03/f49",
        "south" : "r03/f50",
        "northwest" : "r01/f49",
        "east" : "r02/f51",
        "north" : "r01/f50",
        "northeast" : "r01/f51",
        "west" : "r02/f49",
    ]));
    
}

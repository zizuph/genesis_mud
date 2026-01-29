#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r05/f49",
        "southwest" : "r05/f47",
        "south" : "r05/f48",
        "northwest" : "r03/f47",
        "east" : "r04/f49",
        "north" : "r03/f48",
        "northeast" : "r03/f49",
        "west" : "r04/f47",
    ]));
    
}

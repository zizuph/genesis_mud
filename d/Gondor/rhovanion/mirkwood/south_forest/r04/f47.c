#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f48",
        "southwest" : "r05/f46",
        "south" : "r05/f47",
        "northwest" : "r03/f46",
        "east" : "r04/f48",
        "north" : "r03/f47",
        "northeast" : "r03/f48",
        "west" : "r04/f46",
    ]));
    
}

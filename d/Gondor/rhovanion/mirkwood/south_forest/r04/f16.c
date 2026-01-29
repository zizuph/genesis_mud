#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f17",
        "southwest" : "r05/f15",
        "south" : "r05/f16",
        "northwest" : "r03/f15",
        "east" : "r04/f17",
        "north" : "r03/f16",
        "northeast" : "r03/f17",
        "west" : "r04/f15",
    ]));
    
}

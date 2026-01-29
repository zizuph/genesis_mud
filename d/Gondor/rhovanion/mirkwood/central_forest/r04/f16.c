#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(27);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f17",
        "southwest" : "r03/f15",
        "south" : "r03/f16",
        "northwest" : "r05/f15",
        "east" : "r04/f17",
        "north" : "r05/f16",
        "northeast" : "r05/f17",
        "west" : "r04/f15",
    ]));
    
}

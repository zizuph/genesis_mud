#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(23);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r01/f17",
        "southwest" : "r01/f15",
        "south" : "r01/f16",
        "northwest" : "r03/f15",
        "east" : "r02/f17",
        "north" : "r03/f16",
        "northeast" : "r03/f17",
        "west" : "r02/f15",
    ]));
    
}

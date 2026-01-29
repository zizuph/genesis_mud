#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f17",
        "southwest" : "r04/f15",
        "south" : "r04/f16",
        "northwest" : "r02/f15",
        "east" : "r03/f17",
        "north" : "r02/f16",
        "northeast" : "r02/f17",
        "west" : "r03/f15",
    ]));
    
}

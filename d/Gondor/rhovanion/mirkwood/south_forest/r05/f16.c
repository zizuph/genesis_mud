#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f17",
        "southwest" : "r06/f15",
        "south" : "r06/f16",
        "northwest" : "r04/f15",
        "east" : "r05/f17",
        "north" : "r04/f16",
        "northeast" : "r04/f17",
        "west" : "r05/f15",
    ]));
    
}

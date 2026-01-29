#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r33/f17",
        "southwest" : "r33/f15",
        "south" : "r33/f16",
        "northwest" : "r31/f15",
        "east" : "r32/f17",
        "north" : "r31/f16",
        "northeast" : "r31/f17",
        "west" : "r32/f15",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r32/f17",
        "southwest" : "r32/f15",
        "south" : "r32/f16",
        "northwest" : "r30/f15",
        "east" : "r31/f17",
        "north" : "r30/f16",
        "northeast" : "r30/f17",
        "west" : "r31/f15",
    ]));
    
}

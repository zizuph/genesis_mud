#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r31/f17",
        "southwest" : "r31/f15",
        "south" : "r31/f16",
        "northwest" : "r29/f15",
        "east" : "r30/f17",
        "north" : "r29/f16",
        "northeast" : "r29/f17",
        "west" : "r30/f15",
    ]));
    
}

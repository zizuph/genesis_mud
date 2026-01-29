#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f17",
        "southwest" : "r08/f15",
        "south" : "r08/f16",
        "northwest" : "r06/f15",
        "east" : "r07/f17",
        "north" : "r06/f16",
        "northeast" : "r06/f17",
        "west" : "r07/f15",
    ]));
    
}

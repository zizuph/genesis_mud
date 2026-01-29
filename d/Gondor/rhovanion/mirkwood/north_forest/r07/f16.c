#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r06/f17",
        "southwest" : "r06/f15",
        "south" : "r06/f16",
        "northwest" : "r08/f15",
        "east" : "r07/f17",
        "north" : "r08/f16",
        "northeast" : "r08/f17",
        "west" : "r07/f15",
    ]));
    
}

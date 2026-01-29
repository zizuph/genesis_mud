#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(71);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r05/f17",
        "southwest" : "r05/f15",
        "south" : "r05/f16",
        "northwest" : "r07/f15",
        "east" : "r06/f17",
        "north" : "r07/f16",
        "northeast" : "r07/f17",
        "west" : "r06/f15",
    ]));
    
}

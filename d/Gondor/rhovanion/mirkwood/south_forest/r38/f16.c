#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r39/f17",
        "southwest" : "r39/f15",
        "south" : "r39/f16",
        "northwest" : "r37/f15",
        "east" : "r38/f17",
        "north" : "r37/f16",
        "northeast" : "r37/f17",
        "west" : "r38/f15",
    ]));
    
}

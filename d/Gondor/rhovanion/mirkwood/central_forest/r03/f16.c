#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f17",
        "southwest" : "r02/f15",
        "south" : "r02/f16",
        "northwest" : "r04/f15",
        "east" : "r03/f17",
        "north" : "r04/f16",
        "northeast" : "r04/f17",
        "west" : "r03/f15",
    ]));
    
}

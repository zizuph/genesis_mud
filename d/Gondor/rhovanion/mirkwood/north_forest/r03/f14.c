#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(28);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r02/f15",
        "southwest" : "r02/f13",
        "south" : "r02/f14",
        "northwest" : "r04/f13",
        "east" : "r03/f15",
        "north" : "r04/f14",
        "northeast" : "r04/f15",
        "west" : "r03/f13",
    ]));
    
}

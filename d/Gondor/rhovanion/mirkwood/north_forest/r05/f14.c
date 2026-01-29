#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(34);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r04/f15",
        "southwest" : "r04/f13",
        "south" : "r04/f14",
        "northwest" : "r06/f13",
        "east" : "r05/f15",
        "north" : "r06/f14",
        "northeast" : "r06/f15",
        "west" : "r05/f13",
    ]));
    
}

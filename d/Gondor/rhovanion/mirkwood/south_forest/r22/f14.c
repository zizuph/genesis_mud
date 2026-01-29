#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r23/f15",
        "southwest" : "r23/f13",
        "south" : "r23/f14",
        "northwest" : "r21/f13",
        "east" : "r22/f15",
        "north" : "r21/f14",
        "northeast" : "r21/f15",
        "west" : "r22/f13",
    ]));
    
}

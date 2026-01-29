#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r10/f40",
        "southwest" : "r10/f38",
        "south" : "r10/f39",
        "northwest" : "r08/f38",
        "east" : "r09/f40",
        "north" : "r08/f39",
        "northeast" : "r08/f40",
        "west" : "r09/f38",
    ]));
    
}

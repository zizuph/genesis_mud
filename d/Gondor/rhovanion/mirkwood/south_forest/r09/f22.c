#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r10/f23",
        "southwest" : "r10/f21",
        "south" : "r10/f22",
        "northwest" : "r08/f21",
        "east" : "r09/f23",
        "north" : "r08/f22",
        "northeast" : "r08/f23",
        "west" : "r09/f21",
    ]));
    
}

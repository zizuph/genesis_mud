#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r10/f43",
        "southwest" : "r10/f41",
        "south" : "r10/f42",
        "northwest" : "r08/f41",
        "east" : "r09/f43",
        "north" : "r08/f42",
        "northeast" : "r08/f43",
        "west" : "r09/f41",
    ]));
    
}

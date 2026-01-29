#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r10/f42",
        "southwest" : "r10/f40",
        "south" : "r10/f41",
        "northwest" : "r08/f40",
        "east" : "r09/f42",
        "north" : "r08/f41",
        "northeast" : "r08/f42",
        "west" : "r09/f40",
    ]));
    
}

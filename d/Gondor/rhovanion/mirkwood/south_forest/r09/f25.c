#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r10/f26",
        "southwest" : "r10/f24",
        "south" : "r10/f25",
        "northwest" : "r08/f24",
        "east" : "r09/f26",
        "north" : "r08/f25",
        "northeast" : "r08/f26",
        "west" : "r09/f24",
    ]));
    
}

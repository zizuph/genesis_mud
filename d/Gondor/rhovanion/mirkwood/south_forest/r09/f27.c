#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(25);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r10/f28",
        "southwest" : "r10/f26",
        "south" : "r10/f27",
        "northwest" : "r08/f26",
        "east" : "r09/f28",
        "north" : "r08/f27",
        "northeast" : "r08/f28",
        "west" : "r09/f26",
    ]));
    
}

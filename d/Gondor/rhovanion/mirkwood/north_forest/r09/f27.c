#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(23);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f28",
        "southwest" : "r08/f26",
        "south" : "r08/f27",
        "northwest" : "r10/f26",
        "east" : "r09/f28",
        "north" : "r10/f27",
        "northeast" : "r10/f28",
        "west" : "r09/f26",
    ]));
    
}

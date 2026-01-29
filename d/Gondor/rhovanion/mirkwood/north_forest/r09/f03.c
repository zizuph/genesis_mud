#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(23);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r08/f04",
        "southwest" : "r08/f02",
        "south" : "r08/f03",
        "northwest" : "r10/f02",
        "east" : "r09/f04",
        "north" : "r10/f03",
        "northeast" : "r10/f04",
        "west" : "r09/f02",
    ]));
    
}

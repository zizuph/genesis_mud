#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r08/f03",
        "southwest" : "r08/f01",
        "south" : "r08/f02",
        "northwest" : "r10/f01",
        "east" : "r09/f03",
        "north" : "r10/f02",
        "northeast" : "r10/f03",
        "west" : "r09/f01",
    ]));
    
}

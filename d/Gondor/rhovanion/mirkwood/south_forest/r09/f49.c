#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r10/f50",
        "southwest" : "r10/f48",
        "south" : "r10/f49",
        "northwest" : "r08/f48",
        "east" : "r09/f50",
        "north" : "r08/f49",
        "northeast" : "r08/f50",
        "west" : "r09/f48",
    ]));
    
}

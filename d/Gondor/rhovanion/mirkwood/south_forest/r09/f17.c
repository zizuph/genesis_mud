#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r10/f18",
        "southwest" : "r10/f16",
        "south" : "r10/f17",
        "northwest" : "r08/f16",
        "east" : "r09/f18",
        "north" : "r08/f17",
        "northeast" : "r08/f18",
        "west" : "r09/f16",
    ]));
    
}

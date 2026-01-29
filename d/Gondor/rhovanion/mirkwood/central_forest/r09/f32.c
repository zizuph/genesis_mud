#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(33);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r08/f33",
        "southwest" : "r08/f31",
        "south" : "r08/f32",
        "northwest" : "r10/f31",
        "east" : "r09/f33",
        "north" : "r10/f32",
        "northeast" : "r10/f33",
        "west" : "r09/f31",
    ]));
    
}

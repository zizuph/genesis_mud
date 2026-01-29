#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(53);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r08/f34",
        "southwest" : "r08/f32",
        "south" : "r08/f33",
        "northwest" : "r10/f32",
        "east" : "r09/f34",
        "north" : "r10/f33",
        "northeast" : "r10/f34",
        "west" : "r09/f32",
    ]));
    
}

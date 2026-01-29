#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r10/f34",
        "southwest" : "r10/f32",
        "south" : "r10/f33",
        "northwest" : "r08/f32",
        "east" : "r09/f34",
        "north" : "r08/f33",
        "northeast" : "r08/f34",
        "west" : "r09/f32",
    ]));
    
}

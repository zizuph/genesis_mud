#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r10/f33",
        "southwest" : "r10/f31",
        "south" : "r10/f32",
        "northwest" : "r08/f31",
        "east" : "r09/f33",
        "north" : "r08/f32",
        "northeast" : "r08/f33",
        "west" : "r09/f31",
    ]));
    
}

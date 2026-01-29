#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(4);
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

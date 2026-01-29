#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(66);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r06/m34",
        "southwest" : "r06/m32",
        "south" : "r06/m33",
        "northwest" : "r08/f32",
        "east" : "r07/f34",
        "north" : "r08/f33",
        "northeast" : "r08/f34",
        "west" : "r07/f32",
    ]));
    
}

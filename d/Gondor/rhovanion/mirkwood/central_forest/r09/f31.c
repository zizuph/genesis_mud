#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(33);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r08/f32",
        "southwest" : "r08/f30",
        "south" : "r08/f31",
        "northwest" : "r10/f30",
        "east" : "r09/f32",
        "north" : "r10/f31",
        "northeast" : "r10/f32",
        "west" : "r09/f30",
    ]));
    
}

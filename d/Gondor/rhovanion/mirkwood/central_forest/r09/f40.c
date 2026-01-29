#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(57);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f41",
        "southwest" : "r08/f39",
        "south" : "r08/f40",
        "northwest" : "r10/f39",
        "east" : "r09/f41",
        "north" : "r10/f40",
        "northeast" : "r10/f41",
        "west" : "r09/f39",
    ]));
    
}

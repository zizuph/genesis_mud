#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r10/f38",
        "southwest" : "r10/f36",
        "south" : "r10/f37",
        "northwest" : "r08/f36",
        "east" : "r09/f38",
        "north" : "r08/f37",
        "northeast" : "r08/f38",
        "west" : "r09/f36",
    ]));
    
}

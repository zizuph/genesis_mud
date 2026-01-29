#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r10/f39",
        "southwest" : "r10/f37",
        "south" : "r10/f38",
        "northwest" : "r08/f37",
        "east" : "r09/f39",
        "north" : "r08/f38",
        "northeast" : "r08/f39",
        "west" : "r09/f37",
    ]));
    
}

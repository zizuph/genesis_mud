#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r10/f22",
        "southwest" : "r10/f20",
        "south" : "r10/f21",
        "northwest" : "r08/f20",
        "east" : "r09/f22",
        "north" : "r08/f21",
        "northeast" : "r08/f22",
        "west" : "r09/f20",
    ]));
    
}

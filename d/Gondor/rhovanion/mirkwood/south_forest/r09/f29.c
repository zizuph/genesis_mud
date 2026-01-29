#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r10/f30",
        "southwest" : "r10/f28",
        "south" : "r10/f29",
        "northwest" : "r08/f28",
        "east" : "r09/f30",
        "north" : "r08/f29",
        "northeast" : "r08/f30",
        "west" : "r09/f28",
    ]));
    
}

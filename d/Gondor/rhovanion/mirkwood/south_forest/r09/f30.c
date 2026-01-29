#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r10/f31",
        "southwest" : "r10/f29",
        "south" : "r10/f30",
        "northwest" : "r08/f29",
        "east" : "r09/f31",
        "north" : "r08/f30",
        "northeast" : "r08/f31",
        "west" : "r09/f29",
    ]));
    
}

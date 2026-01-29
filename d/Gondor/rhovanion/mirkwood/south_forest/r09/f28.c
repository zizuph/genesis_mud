#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r10/f29",
        "southwest" : "r10/f27",
        "south" : "r10/f28",
        "northwest" : "r08/f27",
        "east" : "r09/f29",
        "north" : "r08/f28",
        "northeast" : "r08/f29",
        "west" : "r09/f27",
    ]));
    
}

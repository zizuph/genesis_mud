#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(23);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f30",
        "southwest" : "r08/f28",
        "south" : "r08/f29",
        "northwest" : "r10/f28",
        "east" : "r09/f30",
        "north" : "r10/f29",
        "northeast" : "r10/f30",
        "west" : "r09/f28",
    ]));
    
}

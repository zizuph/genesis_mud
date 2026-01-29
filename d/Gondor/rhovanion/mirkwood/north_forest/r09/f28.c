#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(20);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f29",
        "southwest" : "r08/f27",
        "south" : "r08/f28",
        "northwest" : "r10/f27",
        "east" : "r09/f29",
        "north" : "r10/f28",
        "northeast" : "r10/f29",
        "west" : "r09/f27",
    ]));
    
}

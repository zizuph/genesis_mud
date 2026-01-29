#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(61);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f29",
        "southwest" : "r00/f27",
        "south" : "r00/f28",
        "northwest" : "r02/f27",
        "east" : "r01/f29",
        "north" : "r02/f28",
        "northeast" : "r02/f29",
        "west" : "r01/f27",
    ]));
    
}

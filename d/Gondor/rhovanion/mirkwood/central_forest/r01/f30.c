#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(37);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f31",
        "southwest" : "r00/f29",
        "south" : "r00/f30",
        "northwest" : "r02/f29",
        "east" : "r01/f31",
        "north" : "r02/f30",
        "northeast" : "r02/f31",
        "west" : "r01/f29",
    ]));
    
}

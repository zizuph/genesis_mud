#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(62);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f30",
        "southwest" : "r00/f28",
        "south" : "r00/f29",
        "northwest" : "r02/f28",
        "east" : "r01/f30",
        "north" : "r02/f29",
        "northeast" : "r02/f30",
        "west" : "r01/f28",
    ]));
    
}

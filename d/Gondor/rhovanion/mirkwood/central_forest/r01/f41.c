#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f42",
        "southwest" : "r00/f40",
        "south" : "r00/f41",
        "northwest" : "r02/f40",
        "east" : "r01/f42",
        "north" : "r02/f41",
        "northeast" : "r02/f42",
        "west" : "r01/f40",
    ]));
    
}

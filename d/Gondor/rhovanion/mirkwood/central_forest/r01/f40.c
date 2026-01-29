#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f41",
        "southwest" : "r00/f39",
        "south" : "r00/f40",
        "northwest" : "r02/f39",
        "east" : "r01/f41",
        "north" : "r02/f40",
        "northeast" : "r02/f41",
        "west" : "r01/f39",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f43",
        "southwest" : "r02/f41",
        "south" : "r02/f42",
        "northwest" : "r00/f41",
        "east" : "r01/p43",
        "north" : "r00/p42",
        "northeast" : "r00/f43",
        "west" : "r01/f41",
    ]));
    
}

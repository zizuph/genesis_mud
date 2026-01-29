#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f41",
        "southwest" : "r02/f39",
        "south" : "r02/f40",
        "northwest" : "r00/f39",
        "east" : "r01/f41",
        "north" : "r00/f40",
        "northeast" : "r00/f41",
        "west" : "r01/f39",
    ]));
    
}

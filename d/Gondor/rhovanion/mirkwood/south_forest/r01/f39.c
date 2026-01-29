#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f40",
        "southwest" : "r02/f38",
        "south" : "r02/f39",
        "northwest" : "r00/f38",
        "east" : "r01/f40",
        "north" : "r00/f39",
        "northeast" : "r00/f40",
        "west" : "r01/f38",
    ]));
    
}

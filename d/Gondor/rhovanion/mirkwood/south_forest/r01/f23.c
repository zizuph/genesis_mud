#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f24",
        "southwest" : "r02/f22",
        "south" : "r02/f23",
        "northwest" : "r00/f22",
        "east" : "r01/f24",
        "north" : "r00/f23",
        "northeast" : "r00/f24",
        "west" : "r01/f22",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f30",
        "southwest" : "r02/f28",
        "south" : "r02/f29",
        "northwest" : "r00/f28",
        "east" : "r01/f30",
        "north" : "r00/f29",
        "northeast" : "r00/f30",
        "west" : "r01/f28",
    ]));
    
}

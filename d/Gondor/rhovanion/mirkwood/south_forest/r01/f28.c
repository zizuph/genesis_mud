#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f29",
        "southwest" : "r02/f27",
        "south" : "r02/f28",
        "northwest" : "r00/f27",
        "east" : "r01/f29",
        "north" : "r00/f28",
        "northeast" : "r00/f29",
        "west" : "r01/f27",
    ]));
    
}

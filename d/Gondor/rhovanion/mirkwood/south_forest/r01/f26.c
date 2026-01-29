#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f27",
        "southwest" : "r02/f25",
        "south" : "r02/f26",
        "northwest" : "r00/f25",
        "east" : "r01/f27",
        "north" : "r00/f26",
        "northeast" : "r00/f27",
        "west" : "r01/f25",
    ]));
    
}

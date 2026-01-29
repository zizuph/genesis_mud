#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f19",
        "southwest" : "r02/f17",
        "south" : "r02/f18",
        "northwest" : "r00/f17",
        "east" : "r01/f19",
        "north" : "r00/f18",
        "northeast" : "r00/f19",
        "west" : "r01/f17",
    ]));
    
}

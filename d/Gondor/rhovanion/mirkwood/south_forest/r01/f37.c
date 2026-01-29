#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(24);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f38",
        "southwest" : "r02/f36",
        "south" : "r02/f37",
        "northwest" : "r00/f36",
        "east" : "r01/f38",
        "north" : "r00/f37",
        "northeast" : "r00/f38",
        "west" : "r01/f36",
    ]));
    
}

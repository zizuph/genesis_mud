#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(23);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f38",
        "southwest" : "r00/f36",
        "south" : "r00/f37",
        "northwest" : "r02/f36",
        "east" : "r01/f38",
        "north" : "r02/f37",
        "northeast" : "r02/f38",
        "west" : "r01/f36",
    ]));
    
}

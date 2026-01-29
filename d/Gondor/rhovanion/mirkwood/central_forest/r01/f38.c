#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f39",
        "southwest" : "r00/f37",
        "south" : "r00/f38",
        "northwest" : "r02/f37",
        "east" : "r01/f39",
        "north" : "r02/f38",
        "northeast" : "r02/f39",
        "west" : "r01/f37",
    ]));
    
}

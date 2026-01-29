#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(43);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f28",
        "southwest" : "r00/f26",
        "south" : "r00/f27",
        "northwest" : "r02/f26",
        "east" : "r01/f28",
        "north" : "r02/f27",
        "northeast" : "r02/f28",
        "west" : "r01/f26",
    ]));
    
}

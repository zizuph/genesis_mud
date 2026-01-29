#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(43);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f27",
        "southwest" : "r00/f25",
        "south" : "r00/f26",
        "northwest" : "r02/f25",
        "east" : "r01/f27",
        "north" : "r02/f26",
        "northeast" : "r02/f27",
        "west" : "r01/f25",
    ]));
    
}

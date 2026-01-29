#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f45",
        "southwest" : "r00/f43",
        "south" : "r00/f44",
        "northwest" : "r02/f43",
        "east" : "r01/f45",
        "north" : "r02/f44",
        "northeast" : "r02/f45",
        "west" : "r01/f43",
    ]));
    
}

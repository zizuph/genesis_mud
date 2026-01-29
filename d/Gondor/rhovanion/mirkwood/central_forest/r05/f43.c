#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(46);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r04/f44",
        "southwest" : "r04/f42",
        "south" : "r04/f43",
        "northwest" : "r06/f42",
        "east" : "r05/f44",
        "north" : "r06/f43",
        "northeast" : "r06/f44",
        "west" : "r05/f42",
    ]));
    
}

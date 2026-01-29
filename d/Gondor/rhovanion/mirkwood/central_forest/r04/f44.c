#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(46);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f45",
        "southwest" : "r03/f43",
        "south" : "r03/f44",
        "northwest" : "r05/f43",
        "east" : "r04/f45",
        "north" : "r05/f44",
        "northeast" : "r05/f45",
        "west" : "r04/f43",
    ]));
    
}

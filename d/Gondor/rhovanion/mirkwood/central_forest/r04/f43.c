#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(50);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f44",
        "southwest" : "r03/f42",
        "south" : "r03/f43",
        "northwest" : "r05/f42",
        "east" : "r04/f44",
        "north" : "r05/f43",
        "northeast" : "r05/f44",
        "west" : "r04/f42",
    ]));
    
}

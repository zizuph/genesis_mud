#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(62);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f43",
        "southwest" : "r03/f41",
        "south" : "r03/f42",
        "northwest" : "r05/f41",
        "east" : "r04/f43",
        "north" : "r05/f42",
        "northeast" : "r05/f43",
        "west" : "r04/f41",
    ]));
    
}

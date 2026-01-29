#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(95);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f40",
        "southwest" : "r03/f38",
        "south" : "r03/f39",
        "northwest" : "r05/m38",
        "east" : "r04/f40",
        "north" : "r05/m39",
        "northeast" : "r05/m40",
        "west" : "r04/m38",
    ]));
    
}

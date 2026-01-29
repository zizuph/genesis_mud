#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(83);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f41",
        "southwest" : "r03/f39",
        "south" : "r03/f40",
        "northwest" : "r05/m39",
        "east" : "r04/f41",
        "north" : "r05/m40",
        "northeast" : "r05/f41",
        "west" : "r04/f39",
    ]));
    
}

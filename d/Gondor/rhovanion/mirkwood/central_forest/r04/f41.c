#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(76);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f42",
        "southwest" : "r03/f40",
        "south" : "r03/f41",
        "northwest" : "r05/m40",
        "east" : "r04/f42",
        "north" : "r05/f41",
        "northeast" : "r05/f42",
        "west" : "r04/f40",
    ]));
    
}

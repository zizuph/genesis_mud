#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(32);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f43",
        "southwest" : "r02/f41",
        "south" : "r02/f42",
        "northwest" : "r04/f41",
        "east" : "r03/f43",
        "north" : "r04/f42",
        "northeast" : "r04/f43",
        "west" : "r03/f41",
    ]));
    
}

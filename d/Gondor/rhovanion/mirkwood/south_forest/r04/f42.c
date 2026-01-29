#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f43",
        "southwest" : "r05/f41",
        "south" : "r05/f42",
        "northwest" : "r03/f41",
        "east" : "r04/f43",
        "north" : "r03/f42",
        "northeast" : "r03/f43",
        "west" : "r04/f41",
    ]));
    
}

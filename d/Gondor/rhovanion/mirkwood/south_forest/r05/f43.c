#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f44",
        "southwest" : "r06/f42",
        "south" : "r06/f43",
        "northwest" : "r04/f42",
        "east" : "r05/f44",
        "north" : "r04/f43",
        "northeast" : "r04/f44",
        "west" : "r05/f42",
    ]));
    
}

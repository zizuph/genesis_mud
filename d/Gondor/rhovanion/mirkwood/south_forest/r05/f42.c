#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f43",
        "southwest" : "r06/f41",
        "south" : "r06/f42",
        "northwest" : "r04/f41",
        "east" : "r05/f43",
        "north" : "r04/f42",
        "northeast" : "r04/f43",
        "west" : "r05/f41",
    ]));
    
}

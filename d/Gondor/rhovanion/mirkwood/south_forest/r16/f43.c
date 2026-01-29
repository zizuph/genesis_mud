#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r17/f44",
        "southwest" : "r17/f42",
        "south" : "r17/f43",
        "northwest" : "r15/f42",
        "east" : "r16/f44",
        "north" : "r15/f43",
        "northeast" : "r15/f44",
        "west" : "r16/f42",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r17/f43",
        "southwest" : "r17/f41",
        "south" : "r17/f42",
        "northwest" : "r15/f41",
        "east" : "r16/f43",
        "north" : "r15/f42",
        "northeast" : "r15/f43",
        "west" : "r16/f41",
    ]));
    
}

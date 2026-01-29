#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r16/f43",
        "southwest" : "r16/f41",
        "south" : "r16/f42",
        "northwest" : "r14/f41",
        "east" : "r15/f43",
        "north" : "r14/f42",
        "northeast" : "r14/f43",
        "west" : "r15/f41",
    ]));
    
}

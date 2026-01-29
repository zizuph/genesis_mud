#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r16/f42",
        "southwest" : "r16/f40",
        "south" : "r16/f41",
        "northwest" : "r14/f40",
        "east" : "r15/f42",
        "north" : "r14/f41",
        "northeast" : "r14/f42",
        "west" : "r15/f40",
    ]));
    
}

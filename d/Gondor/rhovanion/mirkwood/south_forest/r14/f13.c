#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r15/f14",
        "southwest" : "r15/f12",
        "south" : "r15/f13",
        "northwest" : "r13/f12",
        "east" : "r14/f14",
        "north" : "r13/f13",
        "northeast" : "r13/f14",
        "west" : "r14/f12",
    ]));
    
}

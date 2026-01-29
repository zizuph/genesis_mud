#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(12);
    add_mirkwood_exits(([
        "southeast" : "r15/f20",
        "southwest" : "r15/f18",
        "south" : "r15/f19",
        "northwest" : "r13/f18",
        "east" : "r14/f20",
        "north" : "r13/f19",
        "northeast" : "r13/f20",
        "west" : "r14/f18",
    ]));
    
}

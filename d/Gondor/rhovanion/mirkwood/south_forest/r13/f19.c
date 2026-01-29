#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(13);
    add_mirkwood_exits(([
        "southeast" : "r14/f20",
        "southwest" : "r14/f18",
        "south" : "r14/f19",
        "northwest" : "r12/f18",
        "east" : "r13/f20",
        "north" : "r12/f19",
        "northeast" : "r12/f20",
        "west" : "r13/f18",
    ]));
    
}

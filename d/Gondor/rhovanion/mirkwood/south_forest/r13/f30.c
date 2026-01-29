#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(13);
    add_mirkwood_exits(([
        "southeast" : "r14/f31",
        "southwest" : "r14/f29",
        "south" : "r14/f30",
        "northwest" : "r12/f29",
        "east" : "r13/f31",
        "north" : "r12/f30",
        "northeast" : "r12/f31",
        "west" : "r13/f29",
    ]));
    
}

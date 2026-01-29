#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(13);
    add_mirkwood_exits(([
        "southeast" : "r14/f29",
        "southwest" : "r14/f27",
        "south" : "r14/f28",
        "northwest" : "r12/f27",
        "east" : "r13/f29",
        "north" : "r12/f28",
        "northeast" : "r12/f29",
        "west" : "r13/f27",
    ]));
    
}

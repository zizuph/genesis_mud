#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(14);
    add_mirkwood_exits(([
        "southeast" : "r15/f30",
        "southwest" : "r15/f28",
        "south" : "r15/f29",
        "northwest" : "r13/f28",
        "east" : "r14/f30",
        "north" : "r13/f29",
        "northeast" : "r13/f30",
        "west" : "r14/f28",
    ]));
    
}

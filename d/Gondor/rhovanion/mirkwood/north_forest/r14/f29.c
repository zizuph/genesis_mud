#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r13/f30",
        "southwest" : "r13/f28",
        "south" : "r13/f29",
        "northwest" : "r15/f28",
        "east" : "r14/f30",
        "north" : "r15/f29",
        "northeast" : "r15/f30",
        "west" : "r14/f28",
    ]));
    
}

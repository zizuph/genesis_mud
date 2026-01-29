#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r13/f31",
        "southwest" : "r13/f29",
        "south" : "r13/f30",
        "northwest" : "r15/f29",
        "east" : "r14/f31",
        "north" : "r15/f30",
        "northeast" : "r15/f31",
        "west" : "r14/f29",
    ]));
    
}

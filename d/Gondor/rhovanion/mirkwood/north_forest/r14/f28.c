#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r13/f29",
        "southwest" : "r13/f27",
        "south" : "r13/f28",
        "northwest" : "r15/f27",
        "east" : "r14/f29",
        "north" : "r15/f28",
        "northeast" : "r15/f29",
        "west" : "r14/f27",
    ]));
    
}

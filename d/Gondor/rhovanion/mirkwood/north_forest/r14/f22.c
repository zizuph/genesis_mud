#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(29);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r13/f23",
        "southwest" : "r13/f21",
        "south" : "r13/f22",
        "northwest" : "r15/f21",
        "east" : "r14/f23",
        "north" : "r15/f22",
        "northeast" : "r15/f23",
        "west" : "r14/f21",
    ]));
    
}

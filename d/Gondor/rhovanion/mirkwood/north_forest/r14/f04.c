#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r13/f05",
        "southwest" : "r13/f03",
        "south" : "r13/f04",
        "northwest" : "r15/f03",
        "east" : "r14/f05",
        "north" : "r15/f04",
        "northeast" : "r15/f05",
        "west" : "r14/f03",
    ]));
    
}

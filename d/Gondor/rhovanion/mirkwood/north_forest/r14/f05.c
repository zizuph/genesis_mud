#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r13/f06",
        "southwest" : "r13/f04",
        "south" : "r13/f05",
        "northwest" : "r15/f04",
        "east" : "r14/f06",
        "north" : "r15/f05",
        "northeast" : "r15/f06",
        "west" : "r14/f04",
    ]));
    
}

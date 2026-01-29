#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(20);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r13/f08",
        "southwest" : "r13/f06",
        "south" : "r13/f07",
        "northwest" : "r15/f06",
        "east" : "r14/f08",
        "north" : "r15/f07",
        "northeast" : "r15/f08",
        "west" : "r14/f06",
    ]));
    
}

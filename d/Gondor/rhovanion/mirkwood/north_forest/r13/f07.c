#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(38);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r12/f08",
        "southwest" : "r12/f06",
        "south" : "r12/f07",
        "northwest" : "r14/f06",
        "east" : "r13/f08",
        "north" : "r14/f07",
        "northeast" : "r14/f08",
        "west" : "r13/f06",
    ]));
    
}

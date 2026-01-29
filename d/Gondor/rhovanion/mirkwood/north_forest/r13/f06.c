#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(36);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r12/f07",
        "southwest" : "r12/f05",
        "south" : "r12/f06",
        "northwest" : "r14/f05",
        "east" : "r13/f07",
        "north" : "r14/f06",
        "northeast" : "r14/f07",
        "west" : "r13/f05",
    ]));
    
}

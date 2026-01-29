#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(29);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r13/f20",
        "southwest" : "r13/f18",
        "south" : "r13/f19",
        "northwest" : "r15/f18",
        "east" : "r14/f20",
        "north" : "r15/f19",
        "northeast" : "r15/f20",
        "west" : "r14/f18",
    ]));
    
}

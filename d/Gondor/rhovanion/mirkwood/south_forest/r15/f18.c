#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r16/f19",
        "southwest" : "r16/f17",
        "south" : "r16/f18",
        "northwest" : "r14/f17",
        "east" : "r15/f19",
        "north" : "r14/f18",
        "northeast" : "r14/f19",
        "west" : "r15/f17",
    ]));
    
}

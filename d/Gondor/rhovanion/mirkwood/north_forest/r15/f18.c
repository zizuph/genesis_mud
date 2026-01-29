#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(27);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r14/f19",
        "southwest" : "r14/f17",
        "south" : "r14/f18",
        "northwest" : "r16/f17",
        "east" : "r15/f19",
        "north" : "r16/f18",
        "northeast" : "r16/f19",
        "west" : "r15/f17",
    ]));
    
}

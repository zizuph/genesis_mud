#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(27);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r14/f18",
        "southwest" : "r14/f16",
        "south" : "r14/f17",
        "northwest" : "r16/f16",
        "east" : "r15/f18",
        "north" : "r16/f17",
        "northeast" : "r16/f18",
        "west" : "r15/f16",
    ]));
    
}

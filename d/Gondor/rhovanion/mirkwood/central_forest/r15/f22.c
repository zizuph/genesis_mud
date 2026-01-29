#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(44);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r14/f23",
        "southwest" : "r14/f21",
        "south" : "r14/f22",
        "northwest" : "r16/f21",
        "east" : "r15/f23",
        "north" : "r16/f22",
        "northeast" : "r16/f23",
        "west" : "r15/f21",
    ]));
    
}

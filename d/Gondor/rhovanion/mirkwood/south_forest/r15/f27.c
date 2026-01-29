#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(15);
    add_mirkwood_exits(([
        "southeast" : "r16/f28",
        "southwest" : "r16/f26",
        "south" : "r16/f27",
        "northwest" : "r14/f26",
        "east" : "r15/f28",
        "north" : "r14/f27",
        "northeast" : "r14/f28",
        "west" : "r15/f26",
    ]));
    
}

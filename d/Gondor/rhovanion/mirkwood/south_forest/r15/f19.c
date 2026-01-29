#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r16/f20",
        "southwest" : "r16/f18",
        "south" : "r16/f19",
        "northwest" : "r14/f18",
        "east" : "r15/f20",
        "north" : "r14/f19",
        "northeast" : "r14/f20",
        "west" : "r15/f18",
    ]));
    
}

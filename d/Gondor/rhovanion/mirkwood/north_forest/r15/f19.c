#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r14/f20",
        "southwest" : "r14/f18",
        "south" : "r14/f19",
        "northwest" : "r16/f18",
        "east" : "r15/f20",
        "north" : "r16/f19",
        "northeast" : "r16/f20",
        "west" : "r15/f18",
    ]));
    
}

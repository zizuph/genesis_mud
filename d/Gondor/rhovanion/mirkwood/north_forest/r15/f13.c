#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(27);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r14/f14",
        "southwest" : "r14/f12",
        "south" : "r14/f13",
        "northwest" : "r16/f12",
        "east" : "r15/f14",
        "north" : "r16/f13",
        "northeast" : "r16/f13",
        "west" : "r15/f12",
    ]));
    
}

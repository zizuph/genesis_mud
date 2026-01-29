#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(24);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r14/f13",
        "southwest" : "r14/f11",
        "south" : "r14/f12",
        "northwest" : "r16/f11",
        "east" : "r15/f13",
        "north" : "r16/f12",
        "northeast" : "r16/f13",
        "west" : "r15/f11",
    ]));
    
}

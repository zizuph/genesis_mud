#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r14/f11",
        "southwest" : "r14/f09",
        "south" : "r14/f10",
        "northwest" : "r16/f09",
        "east" : "r15/f11",
        "north" : "r16/f10",
        "northeast" : "r16/f11",
        "west" : "r15/f09",
    ]));
    
}

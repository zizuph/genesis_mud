#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(37);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r13/f12",
        "southwest" : "r13/f10",
        "south" : "r13/f11",
        "northwest" : "r15/f10",
        "east" : "r14/f12",
        "north" : "r15/f11",
        "northeast" : "r15/f12",
        "west" : "r14/f10",
    ]));
    
}

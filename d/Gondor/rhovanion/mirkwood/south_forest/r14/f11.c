#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r15/f12",
        "southwest" : "r15/f10",
        "south" : "r15/f11",
        "northwest" : "r13/f10",
        "east" : "r14/f12",
        "north" : "r13/f11",
        "northeast" : "r13/f12",
        "west" : "r14/f10",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r13/f32",
        "southwest" : "r13/f30",
        "south" : "r13/f31",
        "northwest" : "r15/f30",
        "east" : "r14/f32",
        "north" : "r15/f31",
        "northeast" : "r15/f32",
        "west" : "r14/f30",
    ]));
    
}

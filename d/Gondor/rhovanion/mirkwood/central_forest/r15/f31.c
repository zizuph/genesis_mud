#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(38);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r14/f32",
        "southwest" : "r14/f30",
        "south" : "r14/f31",
        "northwest" : "r16/f30",
        "east" : "r15/f32",
        "north" : "r16/f31",
        "northeast" : "r16/f32",
        "west" : "r15/f30",
    ]));
    
}

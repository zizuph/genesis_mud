#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(22);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r15/f32",
        "southwest" : "r15/f30",
        "south" : "r15/f31",
        "northwest" : "r17/f30",
        "east" : "r16/f32",
        "north" : "r17/f31",
        "northeast" : "r17/f32",
        "west" : "r16/f30",
    ]));
    
}

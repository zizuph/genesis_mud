#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r17/f32",
        "southwest" : "r17/f30",
        "south" : "r17/f31",
        "northwest" : "r15/f30",
        "east" : "r16/f32",
        "north" : "r15/f31",
        "northeast" : "r15/f32",
        "west" : "r16/f30",
    ]));
    
}

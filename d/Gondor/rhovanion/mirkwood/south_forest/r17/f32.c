#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r18/f33",
        "southwest" : "r18/f31",
        "south" : "r18/f32",
        "northwest" : "r16/f31",
        "east" : "r17/f33",
        "north" : "r16/f32",
        "northeast" : "r16/f33",
        "west" : "r17/f31",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r18/f34",
        "southwest" : "r18/f32",
        "south" : "r18/f33",
        "northwest" : "r16/f32",
        "east" : "r17/f34",
        "north" : "r16/f33",
        "northeast" : "r16/f34",
        "west" : "r17/f32",
    ]));
    
}

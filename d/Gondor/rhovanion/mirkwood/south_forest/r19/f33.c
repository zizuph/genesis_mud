#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r20/f34",
        "southwest" : "r20/f32",
        "south" : "r20/f33",
        "northwest" : "r18/f32",
        "east" : "r19/f34",
        "north" : "r18/f33",
        "northeast" : "r18/f34",
        "west" : "r19/f32",
    ]));
    
}

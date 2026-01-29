#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r22/f33",
        "southwest" : "r22/f31",
        "south" : "r22/f32",
        "northwest" : "r20/f31",
        "east" : "r21/f33",
        "north" : "r20/f32",
        "northeast" : "r20/f33",
        "west" : "r21/f31",
    ]));
    
}

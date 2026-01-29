#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r20/f32",
        "southwest" : "r20/f30",
        "south" : "r20/f31",
        "northwest" : "r19/f30",
        "east" : "r20/f32",
        "north" : "r19/f31",
        "northeast" : "r19/f32",
        "west" : "r20/f30",
    ]));
    
}

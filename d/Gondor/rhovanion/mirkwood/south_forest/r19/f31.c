#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r20/f32",
        "southwest" : "r20/f30",
        "south" : "r20/f31",
        "northwest" : "r18/f30",
        "east" : "r19/f32",
        "north" : "r18/f31",
        "northeast" : "r18/f32",
        "west" : "r19/f30",
    ]));
    
}

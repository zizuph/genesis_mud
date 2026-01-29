#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r35/f32",
        "southwest" : "r35/f30",
        "south" : "r35/f31",
        "northwest" : "r33/f30",
        "east" : "r34/f32",
        "north" : "r33/f31",
        "northeast" : "r33/f32",
        "west" : "r34/f30",
    ]));
    
}

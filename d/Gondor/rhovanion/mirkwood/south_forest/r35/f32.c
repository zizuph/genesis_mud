#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r36/f33",
        "southwest" : "r36/f31",
        "south" : "r36/f32",
        "northwest" : "r34/f31",
        "east" : "r35/f33",
        "north" : "r34/f32",
        "northeast" : "r34/f33",
        "west" : "r35/f31",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r38/f34",
        "southwest" : "r38/f32",
        "south" : "r38/f33",
        "northwest" : "r36/f32",
        "east" : "r37/f34",
        "north" : "r36/f33",
        "northeast" : "r36/f34",
        "west" : "r37/f32",
    ]));
    
}

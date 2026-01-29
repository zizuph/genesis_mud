#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r40/f33",
        "southwest" : "r40/f31",
        "south" : "r40/f32",
        "northwest" : "r38/f31",
        "east" : "r39/f33",
        "north" : "r38/f32",
        "northeast" : "r38/f33",
        "west" : "r39/f31",
    ]));
    
}

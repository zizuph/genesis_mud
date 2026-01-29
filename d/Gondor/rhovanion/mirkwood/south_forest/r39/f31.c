#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r40/f32",
        "southwest" : "r40/f30",
        "south" : "r40/f31",
        "northwest" : "r38/f30",
        "east" : "r39/f32",
        "north" : "r38/f31",
        "northeast" : "r38/f32",
        "west" : "r39/f30",
    ]));
    
}

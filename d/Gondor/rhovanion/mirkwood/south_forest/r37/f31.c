#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r38/f32",
        "southwest" : "r38/f30",
        "south" : "r38/f31",
        "northwest" : "r36/f30",
        "east" : "r37/f32",
        "north" : "r36/f31",
        "northeast" : "r36/f32",
        "west" : "r37/f30",
    ]));
    
}

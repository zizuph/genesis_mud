#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r39/f32",
        "southwest" : "r39/f30",
        "south" : "r39/f31",
        "northwest" : "r37/f30",
        "east" : "r38/f32",
        "north" : "r37/f31",
        "northeast" : "r37/f32",
        "west" : "r38/f30",
    ]));
    
}

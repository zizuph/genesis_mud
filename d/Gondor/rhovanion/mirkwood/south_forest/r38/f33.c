#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r39/f34",
        "southwest" : "r39/f32",
        "south" : "r39/f33",
        "northwest" : "r37/f32",
        "east" : "r38/f34",
        "north" : "r37/f33",
        "northeast" : "r37/f34",
        "west" : "r38/f32",
    ]));
    
}

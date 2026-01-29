#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r32/f33",
        "southwest" : "r32/f31",
        "south" : "r32/f32",
        "northwest" : "r30/f31",
        "east" : "r31/f33",
        "north" : "r30/f32",
        "northeast" : "r30/f33",
        "west" : "r31/f31",
    ]));
    
}

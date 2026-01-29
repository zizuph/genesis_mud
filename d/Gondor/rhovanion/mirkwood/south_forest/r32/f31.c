#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r33/f32",
        "southwest" : "r33/f30",
        "south" : "r33/f31",
        "northwest" : "r31/f30",
        "east" : "r32/f32",
        "north" : "r31/f31",
        "northeast" : "r31/f32",
        "west" : "r32/f30",
    ]));
    
}

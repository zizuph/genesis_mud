#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r32/f32",
        "southwest" : "r32/f30",
        "south" : "r32/f31",
        "northwest" : "r30/f30",
        "east" : "r31/f32",
        "north" : "r30/f31",
        "northeast" : "r30/f32",
        "west" : "r31/f30",
    ]));
    
}

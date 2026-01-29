#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r32/f22",
        "southwest" : "r32/f20",
        "south" : "r32/f21",
        "northwest" : "r30/f20",
        "east" : "r31/f22",
        "north" : "r30/f21",
        "northeast" : "r30/f22",
        "west" : "r31/f20",
    ]));
    
}

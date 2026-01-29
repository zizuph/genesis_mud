#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r33/f13",
        "southwest" : "r33/f11",
        "south" : "r33/f12",
        "northwest" : "r31/f11",
        "east" : "r32/f13",
        "north" : "r31/f12",
        "northeast" : "r31/f13",
        "west" : "r32/f11",
    ]));
    
}

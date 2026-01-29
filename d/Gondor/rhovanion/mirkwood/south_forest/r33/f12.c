#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r34/f13",
        "southwest" : "r34/f11",
        "south" : "r34/f12",
        "northwest" : "r32/f11",
        "east" : "r33/f13",
        "north" : "r32/f12",
        "northeast" : "r32/f13",
        "west" : "r33/f11",
    ]));
    
}

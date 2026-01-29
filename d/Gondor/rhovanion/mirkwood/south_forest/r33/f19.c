#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r34/f20",
        "southwest" : "r34/f18",
        "south" : "r34/f19",
        "northwest" : "r32/f18",
        "east" : "r33/f20",
        "north" : "r32/f19",
        "northeast" : "r32/f20",
        "west" : "r33/f18",
    ]));
    
}

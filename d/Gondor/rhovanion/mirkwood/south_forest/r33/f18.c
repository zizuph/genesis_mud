#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r34/f19",
        "southwest" : "r34/f17",
        "south" : "r34/f18",
        "northwest" : "r32/f17",
        "east" : "r33/f19",
        "north" : "r32/f18",
        "northeast" : "r32/f19",
        "west" : "r33/f17",
    ]));
    
}

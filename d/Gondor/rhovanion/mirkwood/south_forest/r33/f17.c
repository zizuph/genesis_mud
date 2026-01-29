#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r34/f18",
        "southwest" : "r34/f16",
        "south" : "r34/f17",
        "northwest" : "r32/f16",
        "east" : "r33/f18",
        "north" : "r32/f17",
        "northeast" : "r32/f18",
        "west" : "r33/f16",
    ]));
    
}

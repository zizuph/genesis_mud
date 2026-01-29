#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r35/f18",
        "southwest" : "r35/f16",
        "south" : "r35/f17",
        "northwest" : "r33/f16",
        "east" : "r34/f18",
        "north" : "r33/f17",
        "northeast" : "r33/f18",
        "west" : "r34/f16",
    ]));
    
}

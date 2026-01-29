#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r35/f20",
        "southwest" : "r35/f18",
        "south" : "r35/f19",
        "northwest" : "r33/f18",
        "east" : "r34/f20",
        "north" : "r33/f19",
        "northeast" : "r33/f20",
        "west" : "r34/f18",
    ]));
    
}

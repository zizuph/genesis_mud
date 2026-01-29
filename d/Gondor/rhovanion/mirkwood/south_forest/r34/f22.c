#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r35/f23",
        "southwest" : "r35/f21",
        "south" : "r35/f22",
        "northwest" : "r33/f21",
        "east" : "r34/f23",
        "north" : "r33/f22",
        "northeast" : "r33/f23",
        "west" : "r34/f21",
    ]));
    
}

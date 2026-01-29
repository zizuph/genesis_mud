#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r35/f28",
        "southwest" : "r35/f26",
        "south" : "r35/f27",
        "northwest" : "r33/f26",
        "east" : "r34/f28",
        "north" : "r33/f27",
        "northeast" : "r33/f28",
        "west" : "r34/f26",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r35/f26",
        "southwest" : "r35/f24",
        "south" : "r35/f25",
        "northwest" : "r33/f24",
        "east" : "r34/f26",
        "north" : "r33/f25",
        "northeast" : "r33/f26",
        "west" : "r34/f24",
    ]));
    
}

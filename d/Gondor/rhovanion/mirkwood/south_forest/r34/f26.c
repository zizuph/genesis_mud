#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r35/f27",
        "southwest" : "r35/f25",
        "south" : "r35/f26",
        "northwest" : "r33/f25",
        "east" : "r34/f27",
        "north" : "r33/f26",
        "northeast" : "r33/f27",
        "west" : "r34/f25",
    ]));
    
}

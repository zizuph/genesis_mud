#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r35/f29",
        "southwest" : "r35/f27",
        "south" : "r35/f28",
        "northwest" : "r33/f27",
        "east" : "r34/f29",
        "north" : "r33/f28",
        "northeast" : "r33/f29",
        "west" : "r34/f27",
    ]));
    
}

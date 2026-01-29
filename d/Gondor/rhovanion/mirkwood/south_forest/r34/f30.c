#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r35/f31",
        "southwest" : "r35/f29",
        "south" : "r35/f30",
        "northwest" : "r33/f29",
        "east" : "r34/f31",
        "north" : "r33/f30",
        "northeast" : "r33/f31",
        "west" : "r34/f29",
    ]));
    
}

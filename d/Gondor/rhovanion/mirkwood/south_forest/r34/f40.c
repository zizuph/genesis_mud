#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r35/f41",
        "southwest" : "r35/f39",
        "south" : "r35/f40",
        "northwest" : "r33/f39",
        "east" : "r34/f41",
        "north" : "r33/f40",
        "northeast" : "r33/f41",
        "west" : "r34/f39",
    ]));
    
}

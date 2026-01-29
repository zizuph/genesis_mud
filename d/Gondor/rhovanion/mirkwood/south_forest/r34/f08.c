#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r35/f09",
        "southwest" : "r35/f07",
        "south" : "r35/f08",
        "northwest" : "r33/f07",
        "east" : "r34/f09",
        "north" : "r33/f08",
        "northeast" : "r33/f09",
        "west" : "r34/f07",
    ]));
    
}

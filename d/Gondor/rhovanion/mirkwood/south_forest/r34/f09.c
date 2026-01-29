#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r35/f10",
        "southwest" : "r35/f08",
        "south" : "r35/f09",
        "northwest" : "r33/f08",
        "east" : "r34/f10",
        "north" : "r33/f09",
        "northeast" : "r33/f10",
        "west" : "r34/f08",
    ]));
    
}

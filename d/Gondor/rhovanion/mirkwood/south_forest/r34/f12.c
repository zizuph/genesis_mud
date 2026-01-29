#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r35/f13",
        "southwest" : "r35/f11",
        "south" : "r35/f12",
        "northwest" : "r33/f11",
        "east" : "r34/f13",
        "north" : "r33/f12",
        "northeast" : "r33/f13",
        "west" : "r34/f11",
    ]));
    
}

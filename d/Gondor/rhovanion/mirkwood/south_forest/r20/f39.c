#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r20/f40",
        "southwest" : "r20/f38",
        "south" : "r20/f39",
        "northwest" : "r19/f38",
        "east" : "r20/f40",
        "north" : "r19/f39",
        "northeast" : "r19/f40",
        "west" : "r20/f38",
    ]));
    
}

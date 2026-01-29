#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r20/f21",
        "southwest" : "r20/f19",
        "south" : "r20/f20",
        "northwest" : "r19/f19",
        "east" : "r20/f21",
        "north" : "r19/f20",
        "northeast" : "r19/f21",
        "west" : "r20/f19",
    ]));
    
}

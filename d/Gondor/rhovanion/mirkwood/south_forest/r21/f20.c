#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r22/f21",
        "southwest" : "r22/f19",
        "south" : "r22/f20",
        "northwest" : "r20/f19",
        "east" : "r21/f21",
        "north" : "r20/f20",
        "northeast" : "r20/f21",
        "west" : "r21/f19",
    ]));
    
}

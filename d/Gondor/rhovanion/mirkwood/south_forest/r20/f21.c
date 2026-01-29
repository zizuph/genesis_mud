#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r20/f22",
        "southwest" : "r20/f20",
        "south" : "r20/f21",
        "northwest" : "r19/f20",
        "east" : "r20/f22",
        "north" : "r19/f21",
        "northeast" : "r19/f22",
        "west" : "r20/f20",
    ]));
    
}

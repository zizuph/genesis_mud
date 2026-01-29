#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r22/f22",
        "southwest" : "r22/f20",
        "south" : "r22/f21",
        "northwest" : "r20/f20",
        "east" : "r21/f22",
        "north" : "r20/f21",
        "northeast" : "r20/f22",
        "west" : "r21/f20",
    ]));
    
}

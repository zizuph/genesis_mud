#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r22/f14",
        "southwest" : "r22/f12",
        "south" : "r22/f13",
        "northwest" : "r20/f12",
        "east" : "r21/f14",
        "north" : "r20/f13",
        "northeast" : "r20/f14",
        "west" : "r21/f12",
    ]));
    
}

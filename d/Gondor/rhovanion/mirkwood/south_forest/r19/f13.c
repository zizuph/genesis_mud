#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r20/f14",
        "southwest" : "r20/f12",
        "south" : "r20/f13",
        "northwest" : "r18/f12",
        "east" : "r19/f14",
        "north" : "r18/f13",
        "northeast" : "r18/f14",
        "west" : "r19/f12",
    ]));
    
}

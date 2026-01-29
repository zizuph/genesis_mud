#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r20/f13",
        "southwest" : "r20/f11",
        "south" : "r20/f12",
        "northwest" : "r18/f11",
        "east" : "r19/f13",
        "north" : "r18/f12",
        "northeast" : "r18/f13",
        "west" : "r19/f11",
    ]));
    
}

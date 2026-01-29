#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(13);
    add_mirkwood_exits(([
        "southeast" : "r19/f23",
        "southwest" : "r19/f21",
        "south" : "r19/f22",
        "northwest" : "r17/f21",
        "east" : "r18/f23",
        "north" : "r17/f22",
        "northeast" : "r17/f23",
        "west" : "r18/f21",
    ]));
    
}

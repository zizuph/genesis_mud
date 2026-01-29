#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(13);
    add_mirkwood_exits(([
        "southeast" : "r20/f23",
        "southwest" : "r20/f21",
        "south" : "r20/f22",
        "northwest" : "r18/f21",
        "east" : "r19/f23",
        "north" : "r18/f22",
        "northeast" : "r18/f23",
        "west" : "r19/f21",
    ]));
    
}

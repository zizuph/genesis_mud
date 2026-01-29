#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r19/f45",
        "southwest" : "r19/f43",
        "south" : "r19/f44",
        "northwest" : "r17/f43",
        "east" : "r18/f45",
        "north" : "r17/f44",
        "northeast" : "r17/f45",
        "west" : "r18/f43",
    ]));
    
}

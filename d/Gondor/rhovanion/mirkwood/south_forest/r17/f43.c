#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r18/f44",
        "southwest" : "r18/f42",
        "south" : "r18/f43",
        "northwest" : "r16/f42",
        "east" : "r17/f44",
        "north" : "r16/f43",
        "northeast" : "r16/f44",
        "west" : "r17/f42",
    ]));
    
}

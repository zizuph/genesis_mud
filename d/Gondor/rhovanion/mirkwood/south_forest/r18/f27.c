#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(18);
    add_mirkwood_exits(([
        "southeast" : "r19/f28",
        "southwest" : "r19/f26",
        "south" : "r19/f27",
        "northwest" : "r17/f26",
        "east" : "r18/f28",
        "north" : "r17/f27",
        "northeast" : "r17/f28",
        "west" : "r18/f26",
    ]));
    
}

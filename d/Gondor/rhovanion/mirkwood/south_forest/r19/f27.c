#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(18);
    add_mirkwood_exits(([
        "southeast" : "r20/f28",
        "southwest" : "r20/f26",
        "south" : "r20/f27",
        "northwest" : "r18/f26",
        "east" : "r19/f28",
        "north" : "r18/f27",
        "northeast" : "r18/f28",
        "west" : "r19/f26",
    ]));
    
}

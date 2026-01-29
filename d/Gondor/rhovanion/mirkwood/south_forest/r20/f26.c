#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(16);
    add_mirkwood_exits(([
        "southeast" : "r20/f27",
        "southwest" : "r20/f25",
        "south" : "r20/f26",
        "northwest" : "r19/f25",
        "east" : "r20/f27",
        "north" : "r19/f26",
        "northeast" : "r19/f27",
        "west" : "r20/f25",
    ]));
    
}

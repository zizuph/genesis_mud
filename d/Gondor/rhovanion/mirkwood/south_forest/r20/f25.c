#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(15);
    add_mirkwood_exits(([
        "southeast" : "r20/f26",
        "southwest" : "r20/f24",
        "south" : "r20/f25",
        "northwest" : "r19/f24",
        "east" : "r20/f26",
        "north" : "r19/f25",
        "northeast" : "r19/f26",
        "west" : "r20/f24",
    ]));
    
}

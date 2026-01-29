#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r20/f20",
        "southwest" : "r20/f18",
        "south" : "r20/f19",
        "northwest" : "r18/f18",
        "east" : "r19/f20",
        "north" : "r18/f19",
        "northeast" : "r18/f20",
        "west" : "r19/f18",
    ]));
    
}

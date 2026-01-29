#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r20/f39",
        "southwest" : "r20/f37",
        "south" : "r20/f38",
        "northwest" : "r18/f37",
        "east" : "r19/f39",
        "north" : "r18/f38",
        "northeast" : "r18/f39",
        "west" : "r19/f37",
    ]));
    
}

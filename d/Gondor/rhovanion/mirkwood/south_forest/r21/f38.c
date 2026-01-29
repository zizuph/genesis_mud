#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r22/f39",
        "southwest" : "r22/f37",
        "south" : "r22/f38",
        "northwest" : "r20/f37",
        "east" : "r21/f39",
        "north" : "r20/f38",
        "northeast" : "r20/f39",
        "west" : "r21/f37",
    ]));
    
}

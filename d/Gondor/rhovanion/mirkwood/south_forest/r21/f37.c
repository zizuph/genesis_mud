#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r22/f38",
        "southwest" : "r22/f36",
        "south" : "r22/f37",
        "northwest" : "r20/f36",
        "east" : "r21/f38",
        "north" : "r20/f37",
        "northeast" : "r20/f38",
        "west" : "r21/f36",
    ]));
    
}

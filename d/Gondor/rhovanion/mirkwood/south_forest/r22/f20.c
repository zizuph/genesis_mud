#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r23/f21",
        "southwest" : "r23/f19",
        "south" : "r23/f20",
        "northwest" : "r21/f19",
        "east" : "r22/f21",
        "north" : "r21/f20",
        "northeast" : "r21/f21",
        "west" : "r22/f19",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r22/f19",
        "southwest" : "r22/f17",
        "south" : "r22/f18",
        "northwest" : "r20/f17",
        "east" : "r21/f19",
        "north" : "r20/f18",
        "northeast" : "r20/f19",
        "west" : "r21/f17",
    ]));
    
}

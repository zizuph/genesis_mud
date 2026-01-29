#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r22/f18",
        "southwest" : "r22/f16",
        "south" : "r22/f17",
        "northwest" : "r20/f16",
        "east" : "r21/f18",
        "north" : "r20/f17",
        "northeast" : "r20/f18",
        "west" : "r21/f16",
    ]));
    
}

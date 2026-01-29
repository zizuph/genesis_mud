#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(16);
    add_mirkwood_exits(([
        "southeast" : "r22/f27",
        "southwest" : "r22/f25",
        "south" : "r22/f26",
        "northwest" : "r20/f25",
        "east" : "r21/f27",
        "north" : "r20/f26",
        "northeast" : "r20/f27",
        "west" : "r21/f25",
    ]));
    
}

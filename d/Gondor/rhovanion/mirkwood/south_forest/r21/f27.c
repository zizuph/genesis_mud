#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(17);
    add_mirkwood_exits(([
        "southeast" : "r22/f28",
        "southwest" : "r22/f26",
        "south" : "r22/f27",
        "northwest" : "r20/f26",
        "east" : "r21/f28",
        "north" : "r20/f27",
        "northeast" : "r20/f28",
        "west" : "r21/f26",
    ]));
    
}

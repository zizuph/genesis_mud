#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(15);
    add_mirkwood_exits(([
        "southeast" : "r22/f26",
        "southwest" : "r22/f24",
        "south" : "r22/f25",
        "northwest" : "r20/f24",
        "east" : "r21/f26",
        "north" : "r20/f25",
        "northeast" : "r20/f26",
        "west" : "r21/f24",
    ]));
    
}

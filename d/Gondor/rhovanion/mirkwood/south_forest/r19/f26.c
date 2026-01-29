#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(17);
    add_mirkwood_exits(([
        "southeast" : "r20/f27",
        "southwest" : "r20/f25",
        "south" : "r20/f26",
        "northwest" : "r18/f25",
        "east" : "r19/f27",
        "north" : "r18/f26",
        "northeast" : "r18/f27",
        "west" : "r19/f25",
    ]));
    
}

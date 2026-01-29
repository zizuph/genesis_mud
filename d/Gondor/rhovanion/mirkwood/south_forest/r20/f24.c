#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(14);
    add_mirkwood_exits(([
        "southeast" : "r20/f25",
        "southwest" : "r20/f23",
        "south" : "r20/f24",
        "northwest" : "r19/f23",
        "east" : "r20/f25",
        "north" : "r19/f24",
        "northeast" : "r19/f25",
        "west" : "r20/f23",
    ]));
    
}

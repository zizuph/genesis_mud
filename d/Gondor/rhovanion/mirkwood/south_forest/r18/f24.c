#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(15);
    add_mirkwood_exits(([
        "southeast" : "r19/f25",
        "southwest" : "r19/f23",
        "south" : "r19/f24",
        "northwest" : "r17/f23",
        "east" : "r18/f25",
        "north" : "r17/f24",
        "northeast" : "r17/f25",
        "west" : "r18/f23",
    ]));
    
}

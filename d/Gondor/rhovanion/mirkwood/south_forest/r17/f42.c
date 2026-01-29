#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r18/f43",
        "southwest" : "r18/f41",
        "south" : "r18/f42",
        "northwest" : "r16/f41",
        "east" : "r17/f43",
        "north" : "r16/f42",
        "northeast" : "r16/f43",
        "west" : "r17/f41",
    ]));
    
}

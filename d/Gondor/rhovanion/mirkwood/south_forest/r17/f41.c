#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r18/f42",
        "southwest" : "r18/f40",
        "south" : "r18/f41",
        "northwest" : "r16/f40",
        "east" : "r17/f42",
        "north" : "r16/f41",
        "northeast" : "r16/f42",
        "west" : "r17/f40",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r18/f40",
        "southwest" : "r18/f38",
        "south" : "r18/f39",
        "northwest" : "r16/f38",
        "east" : "r17/f40",
        "north" : "r16/f39",
        "northeast" : "r16/f40",
        "west" : "r17/f38",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r18/f41",
        "southwest" : "r18/f39",
        "south" : "r18/f40",
        "northwest" : "r16/f39",
        "east" : "r17/f41",
        "north" : "r16/f40",
        "northeast" : "r16/f41",
        "west" : "r17/f39",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r17/f39",
        "southwest" : "r17/f37",
        "south" : "r17/f38",
        "northwest" : "r15/f37",
        "east" : "r16/f39",
        "north" : "r15/f38",
        "northeast" : "r15/f39",
        "west" : "r16/f37",
    ]));
    
}

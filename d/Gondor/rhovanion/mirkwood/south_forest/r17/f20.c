#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(12);
    add_mirkwood_exits(([
        "southeast" : "r18/f21",
        "southwest" : "r18/f19",
        "south" : "r18/f20",
        "northwest" : "r16/f19",
        "east" : "r17/f21",
        "north" : "r16/f20",
        "northeast" : "r16/f21",
        "west" : "r17/f19",
    ]));
    
}

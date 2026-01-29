#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r18/f14",
        "southwest" : "r18/f12",
        "south" : "r18/f13",
        "northwest" : "r16/f12",
        "east" : "r17/f14",
        "north" : "r16/f13",
        "northeast" : "r16/f14",
        "west" : "r17/f12",
    ]));
    
}

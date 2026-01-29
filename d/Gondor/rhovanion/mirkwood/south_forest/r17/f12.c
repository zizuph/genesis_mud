#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r18/f13",
        "southwest" : "r18/f11",
        "south" : "r18/f12",
        "northwest" : "r16/f11",
        "east" : "r17/f13",
        "north" : "r16/f12",
        "northeast" : "r16/f13",
        "west" : "r17/f11",
    ]));
    
}

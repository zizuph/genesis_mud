#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(13);
    add_mirkwood_exits(([
        "southeast" : "r18/f22",
        "southwest" : "r18/f20",
        "south" : "r18/f21",
        "northwest" : "r16/f20",
        "east" : "r17/f22",
        "north" : "r16/f21",
        "northeast" : "r16/f22",
        "west" : "r17/f20",
    ]));
    
}

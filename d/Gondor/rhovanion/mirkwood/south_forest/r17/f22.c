#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(14);
    add_mirkwood_exits(([
        "southeast" : "r18/f23",
        "southwest" : "r18/f21",
        "south" : "r18/f22",
        "northwest" : "r16/f21",
        "east" : "r17/f23",
        "north" : "r16/f22",
        "northeast" : "r16/f23",
        "west" : "r17/f21",
    ]));
    
}

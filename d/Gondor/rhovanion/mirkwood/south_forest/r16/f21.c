#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(13);
    add_mirkwood_exits(([
        "southeast" : "r17/f22",
        "southwest" : "r17/f20",
        "south" : "r17/f21",
        "northwest" : "r15/f20",
        "east" : "r16/f22",
        "north" : "r15/f21",
        "northeast" : "r15/f22",
        "west" : "r16/f20",
    ]));
    
}

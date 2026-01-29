#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(13);
    add_mirkwood_exits(([
        "southeast" : "r16/f22",
        "southwest" : "r16/f20",
        "south" : "r16/f21",
        "northwest" : "r14/f20",
        "east" : "r15/f22",
        "north" : "r14/f21",
        "northeast" : "r14/f22",
        "west" : "r15/f20",
    ]));
    
}

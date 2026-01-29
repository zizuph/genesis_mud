#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r15/f21",
        "southwest" : "r15/f19",
        "south" : "r15/f20",
        "northwest" : "r17/f19",
        "east" : "r16/f21",
        "north" : "r17/f20",
        "northeast" : "r17/f21",
        "west" : "r16/f19",
    ]));
    
}

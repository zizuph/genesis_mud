#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r17/f20",
        "southwest" : "r17/f18",
        "south" : "r17/f19",
        "northwest" : "r15/f18",
        "east" : "r16/f20",
        "north" : "r15/f19",
        "northeast" : "r15/f20",
        "west" : "r16/f18",
    ]));
    
}

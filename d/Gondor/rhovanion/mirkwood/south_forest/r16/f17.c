#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r17/f18",
        "southwest" : "r17/f16",
        "south" : "r17/f17",
        "northwest" : "r15/f16",
        "east" : "r16/f18",
        "north" : "r15/f17",
        "northeast" : "r15/f18",
        "west" : "r16/f16",
    ]));
    
}

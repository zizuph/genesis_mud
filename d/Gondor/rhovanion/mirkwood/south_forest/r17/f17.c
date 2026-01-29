#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r18/f18",
        "southwest" : "r18/f16",
        "south" : "r18/f17",
        "northwest" : "r16/f16",
        "east" : "r17/f18",
        "north" : "r16/f17",
        "northeast" : "r16/f18",
        "west" : "r17/f16",
    ]));
    
}

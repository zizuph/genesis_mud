#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(23);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r16/f33",
        "southwest" : "r16/f31",
        "south" : "r16/f32",
        "northwest" : "r18/f31",
        "east" : "r17/f33",
        "north" : "r18/f32",
        "northeast" : "r18/f33",
        "west" : "r17/f31",
    ]));
    
}

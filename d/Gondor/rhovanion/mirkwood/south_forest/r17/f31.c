#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r18/f32",
        "southwest" : "r18/f30",
        "south" : "r18/f31",
        "northwest" : "r16/f30",
        "east" : "r17/f32",
        "north" : "r16/f31",
        "northeast" : "r16/f32",
        "west" : "r17/f30",
    ]));
    
}

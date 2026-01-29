#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r16/f18",
        "southwest" : "r16/f16",
        "south" : "r16/f17",
        "northwest" : "r18/f16",
        "east" : "r17/f18",
        "north" : "r18/f17",
        "northeast" : "r18/f18",
        "west" : "r17/f16",
    ]));
    
}

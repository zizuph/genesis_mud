#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r16/f19",
        "southwest" : "r16/f17",
        "south" : "r16/f18",
        "northwest" : "r18/f17",
        "east" : "r17/f19",
        "north" : "r18/f18",
        "northeast" : "r18/f19",
        "west" : "r17/f17",
    ]));
    
}

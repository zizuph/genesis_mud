#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r17/f19",
        "southwest" : "r17/f17",
        "south" : "r17/f18",
        "northwest" : "r19/f17",
        "east" : "r18/f19",
        "north" : "r19/f18",
        "northeast" : "r19/f19",
        "west" : "r18/f17",
    ]));
    
}

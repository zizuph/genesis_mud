#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r30/f19",
        "southwest" : "r30/f17",
        "south" : "r30/f18",
        "northwest" : "r28/f17",
        "east" : "r29/f19",
        "north" : "r28/f18",
        "northeast" : "r28/f19",
        "west" : "r29/f17",
    ]));
    
}

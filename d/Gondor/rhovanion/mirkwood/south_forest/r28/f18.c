#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r29/f19",
        "southwest" : "r29/f17",
        "south" : "r29/f18",
        "northwest" : "r27/f17",
        "east" : "r28/f19",
        "north" : "r27/f18",
        "northeast" : "r27/f19",
        "west" : "r28/f17",
    ]));
    
}

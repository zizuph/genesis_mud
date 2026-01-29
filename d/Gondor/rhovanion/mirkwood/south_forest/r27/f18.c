#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r28/f19",
        "southwest" : "r28/f17",
        "south" : "r28/f18",
        "northwest" : "r26/f17",
        "east" : "r27/f19",
        "north" : "r26/f18",
        "northeast" : "r26/f19",
        "west" : "r27/f17",
    ]));
    
}

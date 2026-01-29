#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r28/f18",
        "southwest" : "r28/f16",
        "south" : "r28/f17",
        "northwest" : "r26/f16",
        "east" : "r27/f18",
        "north" : "r26/f17",
        "northeast" : "r26/f18",
        "west" : "r27/f16",
    ]));
    
}

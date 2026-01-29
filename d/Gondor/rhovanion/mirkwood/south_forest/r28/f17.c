#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r29/f18",
        "southwest" : "r29/f16",
        "south" : "r29/f17",
        "northwest" : "r27/f16",
        "east" : "r28/f18",
        "north" : "r27/f17",
        "northeast" : "r27/f18",
        "west" : "r28/f16",
    ]));
    
}

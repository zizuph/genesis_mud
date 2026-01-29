#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r29/f21",
        "southwest" : "r29/f19",
        "south" : "r29/f20",
        "northwest" : "r27/f19",
        "east" : "r28/f21",
        "north" : "r27/f20",
        "northeast" : "r27/f21",
        "west" : "r28/f19",
    ]));
    
}

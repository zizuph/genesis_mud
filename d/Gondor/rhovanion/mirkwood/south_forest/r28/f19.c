#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r29/f20",
        "southwest" : "r29/f18",
        "south" : "r29/f19",
        "northwest" : "r27/f18",
        "east" : "r28/f20",
        "north" : "r27/f19",
        "northeast" : "r27/f20",
        "west" : "r28/f18",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r28/f20",
        "southwest" : "r28/f18",
        "south" : "r28/f19",
        "northwest" : "r26/f18",
        "east" : "r27/f20",
        "north" : "r26/f19",
        "northeast" : "r26/f20",
        "west" : "r27/f18",
    ]));
    
}

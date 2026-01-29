#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r28/f26",
        "southwest" : "r28/f24",
        "south" : "r28/f25",
        "northwest" : "r26/f24",
        "east" : "r27/f26",
        "north" : "r26/f25",
        "northeast" : "r26/f26",
        "west" : "r27/f24",
    ]));
    
}

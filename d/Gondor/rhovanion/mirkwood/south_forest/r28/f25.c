#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r29/f26",
        "southwest" : "r29/f24",
        "south" : "r29/f25",
        "northwest" : "r27/f24",
        "east" : "r28/f26",
        "north" : "r27/f25",
        "northeast" : "r27/f26",
        "west" : "r28/f24",
    ]));
    
}

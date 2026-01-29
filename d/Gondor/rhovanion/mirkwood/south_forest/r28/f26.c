#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r29/f27",
        "southwest" : "r29/f25",
        "south" : "r29/f26",
        "northwest" : "r27/f25",
        "east" : "r28/f27",
        "north" : "r27/f26",
        "northeast" : "r27/f27",
        "west" : "r28/f25",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(12);
    add_mirkwood_exits(([
        "southeast" : "r30/f28",
        "southwest" : "r30/f26",
        "south" : "r30/f27",
        "northwest" : "r28/f26",
        "east" : "r29/f28",
        "north" : "r28/f27",
        "northeast" : "r28/f28",
        "west" : "r29/f26",
    ]));
    
}

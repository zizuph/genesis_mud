#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(13);
    add_mirkwood_exits(([
        "southeast" : "r30/f27",
        "southwest" : "r30/f25",
        "south" : "r30/f26",
        "northwest" : "r28/f25",
        "east" : "r29/f27",
        "north" : "r28/f26",
        "northeast" : "r28/f27",
        "west" : "r29/f25",
    ]));
    
}

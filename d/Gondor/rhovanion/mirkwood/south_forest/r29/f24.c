#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r30/f25",
        "southwest" : "r30/f23",
        "south" : "r30/f24",
        "northwest" : "r28/f23",
        "east" : "r29/f25",
        "north" : "r28/f24",
        "northeast" : "r28/f25",
        "west" : "r29/f23",
    ]));
    
}

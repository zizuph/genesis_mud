#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r30/f23",
        "southwest" : "r30/f21",
        "south" : "r30/f22",
        "northwest" : "r28/f21",
        "east" : "r29/f23",
        "north" : "r28/f22",
        "northeast" : "r28/f23",
        "west" : "r29/f21",
    ]));
    
}

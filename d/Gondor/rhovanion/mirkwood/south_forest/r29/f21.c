#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r30/f22",
        "southwest" : "r30/f20",
        "south" : "r30/f21",
        "northwest" : "r28/f20",
        "east" : "r29/f22",
        "north" : "r28/f21",
        "northeast" : "r28/f22",
        "west" : "r29/f20",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r30/f31",
        "southwest" : "r30/f29",
        "south" : "r30/f30",
        "northwest" : "r28/f29",
        "east" : "r29/f31",
        "north" : "r28/f30",
        "northeast" : "r28/f31",
        "west" : "r29/f29",
    ]));
    
}

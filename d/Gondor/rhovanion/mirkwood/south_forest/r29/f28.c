#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r30/f29",
        "southwest" : "r30/f27",
        "south" : "r30/f28",
        "northwest" : "r28/f27",
        "east" : "r29/f29",
        "north" : "r28/f28",
        "northeast" : "r28/f29",
        "west" : "r29/f27",
    ]));
    
}

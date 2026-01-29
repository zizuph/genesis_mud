#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r31/f23",
        "southwest" : "r31/f21",
        "south" : "r31/f22",
        "northwest" : "r29/f21",
        "east" : "r30/f23",
        "north" : "r29/f22",
        "northeast" : "r29/f23",
        "west" : "r30/f21",
    ]));
    
}

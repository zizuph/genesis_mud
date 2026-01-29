#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r31/f35",
        "southwest" : "r31/f33",
        "south" : "r31/f34",
        "northwest" : "r29/f33",
        "east" : "r30/f35",
        "north" : "r29/f34",
        "northeast" : "r29/f35",
        "west" : "r30/f33",
    ]));
    
}

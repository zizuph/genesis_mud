#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r32/f36",
        "southwest" : "r32/f34",
        "south" : "r32/f35",
        "northwest" : "r30/f34",
        "east" : "r31/f36",
        "north" : "r30/f35",
        "northeast" : "r30/f36",
        "west" : "r31/f34",
    ]));
    
}

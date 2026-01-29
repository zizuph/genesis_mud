#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r32/f37",
        "southwest" : "r32/f35",
        "south" : "r32/f36",
        "northwest" : "r30/f35",
        "east" : "r31/f37",
        "north" : "r30/f36",
        "northeast" : "r30/f37",
        "west" : "r31/f35",
    ]));
    
}

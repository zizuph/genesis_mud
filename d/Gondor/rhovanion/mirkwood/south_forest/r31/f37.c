#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r32/f38",
        "southwest" : "r32/f36",
        "south" : "r32/f37",
        "northwest" : "r30/f36",
        "east" : "r31/f38",
        "north" : "r30/f37",
        "northeast" : "r30/f38",
        "west" : "r31/f36",
    ]));
    
}

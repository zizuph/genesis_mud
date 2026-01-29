#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r32/f14",
        "southwest" : "r32/f12",
        "south" : "r32/f13",
        "northwest" : "r30/f12",
        "east" : "r31/f14",
        "north" : "r30/f13",
        "northeast" : "r30/f14",
        "west" : "r31/f12",
    ]));
    
}

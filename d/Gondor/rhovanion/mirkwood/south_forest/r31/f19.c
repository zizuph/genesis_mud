#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r32/f20",
        "southwest" : "r32/f18",
        "south" : "r32/f19",
        "northwest" : "r30/f18",
        "east" : "r31/f20",
        "north" : "r30/f19",
        "northeast" : "r30/f20",
        "west" : "r31/f18",
    ]));
    
}

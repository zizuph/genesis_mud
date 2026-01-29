#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r33/f20",
        "southwest" : "r33/f18",
        "south" : "r33/f19",
        "northwest" : "r31/f18",
        "east" : "r32/f20",
        "north" : "r31/f19",
        "northeast" : "r31/f20",
        "west" : "r32/f18",
    ]));
    
}

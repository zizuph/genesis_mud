#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r33/f19",
        "southwest" : "r33/f17",
        "south" : "r33/f18",
        "northwest" : "r31/f17",
        "east" : "r32/f19",
        "north" : "r31/f18",
        "northeast" : "r31/f19",
        "west" : "r32/f17",
    ]));
    
}

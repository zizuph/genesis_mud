#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r32/f19",
        "southwest" : "r32/f17",
        "south" : "r32/f18",
        "northwest" : "r30/f17",
        "east" : "r31/f19",
        "north" : "r30/f18",
        "northeast" : "r30/f19",
        "west" : "r31/f17",
    ]));
    
}

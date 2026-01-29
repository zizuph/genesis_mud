#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r33/f27",
        "southwest" : "r33/f25",
        "south" : "r33/f26",
        "northwest" : "r31/f25",
        "east" : "r32/f27",
        "north" : "r31/f26",
        "northeast" : "r31/f27",
        "west" : "r32/f25",
    ]));
    
}

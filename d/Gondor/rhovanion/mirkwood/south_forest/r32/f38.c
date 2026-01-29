#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r33/f39",
        "southwest" : "r33/f37",
        "south" : "r33/f38",
        "northwest" : "r31/f37",
        "east" : "r32/f39",
        "north" : "r31/f38",
        "northeast" : "r31/f39",
        "west" : "r32/f37",
    ]));
    
}

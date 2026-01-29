#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r32/f41",
        "southwest" : "r32/f39",
        "south" : "r32/f40",
        "northwest" : "r30/f39",
        "east" : "r31/f41",
        "north" : "r30/f40",
        "northeast" : "r30/f41",
        "west" : "r31/f39",
    ]));
    
}

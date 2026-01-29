#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r34/f12",
        "southwest" : "r34/f10",
        "south" : "r34/f11",
        "northwest" : "r32/f10",
        "east" : "r33/f12",
        "north" : "r32/f11",
        "northeast" : "r32/f12",
        "west" : "r33/f10",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r35/f12",
        "southwest" : "r35/f10",
        "south" : "r35/f11",
        "northwest" : "r33/f10",
        "east" : "r34/f12",
        "north" : "r33/f11",
        "northeast" : "r33/f12",
        "west" : "r34/f10",
    ]));
    
}

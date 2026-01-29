#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r35/f24",
        "southwest" : "r35/f22",
        "south" : "r35/f23",
        "northwest" : "r33/f22",
        "east" : "r34/f24",
        "north" : "r33/f23",
        "northeast" : "r33/f24",
        "west" : "r34/f22",
    ]));
    
}

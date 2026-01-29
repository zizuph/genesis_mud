#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r36/f22",
        "southwest" : "r36/f20",
        "south" : "r36/f21",
        "northwest" : "r34/f20",
        "east" : "r35/f22",
        "north" : "r34/f21",
        "northeast" : "r34/f22",
        "west" : "r35/f20",
    ]));
    
}

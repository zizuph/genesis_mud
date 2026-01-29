#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r36/f23",
        "southwest" : "r36/f21",
        "south" : "r36/f22",
        "northwest" : "r34/f21",
        "east" : "r35/f23",
        "north" : "r34/f22",
        "northeast" : "r34/f23",
        "west" : "r35/f21",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southeast" : "r36/f13",
        "southwest" : "r36/f11",
        "northwest" : "r34/f11",
        "east" : "r35/f13",
        "north" : "r34/f12",
        "northeast" : "r34/f13",
        "west" : "r35/f11",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r38/f22",
        "southwest" : "r38/f20",
        "south" : "r38/f21",
        "northwest" : "r36/f20",
        "east" : "r37/f22",
        "north" : "r36/f21",
        "northeast" : "r36/f22",
        "west" : "r37/f20",
    ]));
    
}

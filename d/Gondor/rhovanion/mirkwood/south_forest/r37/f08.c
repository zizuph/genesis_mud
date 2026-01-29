#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r38/p09",
        "southwest" : "r38/f07",
        "south" : "r38/f08",
        "northwest" : "r36/f07",
        "east" : "r37/f09",
        "north" : "r36/f08",
        "northeast" : "r36/f09",
        "west" : "r37/f07",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r38/f10",
        "southwest" : "r38/f08",
        "south" : "r38/p09",
        "northwest" : "r36/f08",
        "east" : "r37/p10",
        "north" : "r36/f09",
        "northeast" : "r36/f10",
        "west" : "r37/f08",
    ]));
    
}

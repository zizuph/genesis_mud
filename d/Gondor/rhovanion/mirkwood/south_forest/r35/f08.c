#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r36/f09",
        "southwest" : "r36/f07",
        "south" : "r36/f08",
        "northwest" : "r34/f07",
        "east" : "r35/f09",
        "north" : "r34/f08",
        "northeast" : "r34/f09",
        "west" : "r35/f07",
    ]));
    
}

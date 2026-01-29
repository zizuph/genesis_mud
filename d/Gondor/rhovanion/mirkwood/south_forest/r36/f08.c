#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r37/f09",
        "southwest" : "r37/f07",
        "south" : "r37/f08",
        "northwest" : "r35/f07",
        "east" : "r36/f09",
        "north" : "r35/f08",
        "northeast" : "r35/f09",
        "west" : "r36/f07",
    ]));
    
}

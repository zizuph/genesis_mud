#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r37/p11",
        "southwest" : "r37/f09",
        "south" : "r37/p10",
        "northwest" : "r35/f09",
        "east" : "r36/f11",
        "north" : "r35/f10",
        "northeast" : "r35/f11",
        "west" : "r36/f09",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r37/f25",
        "southwest" : "r37/f23",
        "south" : "r37/f24",
        "northwest" : "r35/f23",
        "east" : "r36/f25",
        "north" : "r35/f24",
        "northeast" : "r35/f25",
        "west" : "r36/f23",
    ]));
    
}

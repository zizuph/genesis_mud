#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r37/f20",
        "southwest" : "r37/f18",
        "south" : "r37/f19",
        "northwest" : "r35/f18",
        "east" : "r36/f20",
        "north" : "r35/f19",
        "northeast" : "r35/f20",
        "west" : "r36/f18",
    ]));
    
}

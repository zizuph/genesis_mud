#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r37/f18",
        "southwest" : "r37/f16",
        "south" : "r37/f17",
        "northwest" : "r35/f16",
        "east" : "r36/f18",
        "north" : "r35/f17",
        "northeast" : "r35/f18",
        "west" : "r36/f16",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r37/f29",
        "southwest" : "r37/f27",
        "south" : "r37/f28",
        "northwest" : "r35/f27",
        "east" : "r36/f29",
        "north" : "r35/f28",
        "northeast" : "r35/f29",
        "west" : "r36/f27",
    ]));
    
}

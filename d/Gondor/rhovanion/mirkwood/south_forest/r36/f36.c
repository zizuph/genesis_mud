#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r37/f37",
        "southwest" : "r37/f35",
        "south" : "r37/f36",
        "northwest" : "r35/f35",
        "east" : "r36/f37",
        "north" : "r35/f36",
        "northeast" : "r35/f37",
        "west" : "r36/f35",
    ]));
    
}

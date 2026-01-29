#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r38/f37",
        "southwest" : "r38/f35",
        "south" : "r38/f36",
        "northwest" : "r36/f35",
        "east" : "r37/f37",
        "north" : "r36/f36",
        "northeast" : "r36/f37",
        "west" : "r37/f35",
    ]));
    
}

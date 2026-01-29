#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r38/f27",
        "southwest" : "r38/f25",
        "south" : "r38/f26",
        "northwest" : "r36/f25",
        "east" : "r37/f27",
        "north" : "r36/f26",
        "northeast" : "r36/f27",
        "west" : "r37/f25",
    ]));
    
}

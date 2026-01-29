#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r38/f19",
        "southwest" : "r38/f17",
        "south" : "r38/f18",
        "northwest" : "r36/f17",
        "east" : "r37/f19",
        "north" : "r36/f18",
        "northeast" : "r36/f19",
        "west" : "r37/f17",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r39/f19",
        "southwest" : "r39/f17",
        "south" : "r39/f18",
        "northwest" : "r37/f17",
        "east" : "r38/f19",
        "north" : "r37/f18",
        "northeast" : "r37/f19",
        "west" : "r38/f17",
    ]));
    
}

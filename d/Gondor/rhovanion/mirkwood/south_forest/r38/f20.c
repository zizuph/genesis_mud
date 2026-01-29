#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r39/f21",
        "southwest" : "r39/f19",
        "south" : "r39/f20",
        "northwest" : "r37/f19",
        "east" : "r38/f21",
        "north" : "r37/f20",
        "northeast" : "r37/f21",
        "west" : "r38/f19",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r39/f13",
        "southwest" : "r39/f11",
        "south" : "r39/f12",
        "northwest" : "r37/p11",
        "east" : "r38/f13",
        "north" : "r37/f12",
        "northeast" : "r37/f13",
        "west" : "r38/f11",
    ]));
    
}

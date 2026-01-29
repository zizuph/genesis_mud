#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r39/f22",
        "southwest" : "r39/f20",
        "south" : "r39/f21",
        "northwest" : "r37/f20",
        "east" : "r38/f22",
        "north" : "r37/f21",
        "northeast" : "r37/f22",
        "west" : "r38/f20",
    ]));
    
}

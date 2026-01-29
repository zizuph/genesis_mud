#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r40/f23",
        "southwest" : "r40/f21",
        "south" : "r40/f22",
        "northwest" : "r38/f21",
        "east" : "r39/f23",
        "north" : "r38/f22",
        "northeast" : "r38/f23",
        "west" : "r39/f21",
    ]));
    
}

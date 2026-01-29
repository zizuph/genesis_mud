#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r40/f26",
        "southwest" : "r40/f24",
        "south" : "r40/f25",
        "northwest" : "r38/f24",
        "east" : "r39/f26",
        "north" : "r38/f25",
        "northeast" : "r38/f26",
        "west" : "r39/f24",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r40/f18",
        "southwest" : "r40/f16",
        "south" : "r40/f17",
        "northwest" : "r38/f16",
        "east" : "r39/f18",
        "north" : "r38/f17",
        "northeast" : "r38/f18",
        "west" : "r39/f16",
    ]));
    
}

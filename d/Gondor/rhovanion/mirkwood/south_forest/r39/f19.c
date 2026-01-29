#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r40/f20",
        "southwest" : "r40/f18",
        "south" : "r40/f19",
        "northwest" : "r38/f18",
        "east" : "r39/f20",
        "north" : "r38/f19",
        "northeast" : "r38/f20",
        "west" : "r39/f18",
    ]));
    
}

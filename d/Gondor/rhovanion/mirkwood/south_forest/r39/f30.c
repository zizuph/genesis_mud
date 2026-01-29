#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r40/f31",
        "southwest" : "r40/f29",
        "south" : "r40/f30",
        "northwest" : "r38/f29",
        "east" : "r39/f31",
        "north" : "r38/f30",
        "northeast" : "r38/f31",
        "west" : "r39/f29",
    ]));
    
}

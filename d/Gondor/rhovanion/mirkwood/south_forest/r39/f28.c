#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r40/f29",
        "southwest" : "r40/f27",
        "south" : "r40/f28",
        "northwest" : "r38/f27",
        "east" : "r39/f29",
        "north" : "r38/f28",
        "northeast" : "r38/f29",
        "west" : "r39/f27",
    ]));
    
}

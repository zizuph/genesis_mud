#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : "r40/f34",
        "south" : "r40/f35",
        "northwest" : "r38/f34",
        "east" : "r39/f36",
        "north" : "r38/f35",
        "northeast" : "r38/f36",
        "west" : "r39/f34",
    ]));
    
}

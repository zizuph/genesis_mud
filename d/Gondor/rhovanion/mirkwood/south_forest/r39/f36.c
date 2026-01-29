#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r40/f35",
        "northwest" : "r38/f35",
        "north" : "r38/f36",
        "northeast" : "r38/f37",
        "west" : "r39/f35",
    ]));
    
}

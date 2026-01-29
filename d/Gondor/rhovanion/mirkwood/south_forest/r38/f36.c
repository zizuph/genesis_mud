#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : "r39/f35",
        "south" : "r39/f36",
        "northwest" : "r37/f35",
        "east" : "r38/f37",
        "north" : "r37/f36",
        "northeast" : "r37/f37",
        "west" : "r38/f35",
    ]));
    
}

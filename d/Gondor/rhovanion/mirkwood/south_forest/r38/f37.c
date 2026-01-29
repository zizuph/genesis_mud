#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r39/f36",
        "northwest" : "r37/f36",
        "north" : "r37/f37",
        "northeast" : "r37/f38",
        "west" : "r38/f36",
    ]));
    
}

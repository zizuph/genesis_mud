#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r04/f36",
        "south" : "r04/f37",
        "northwest" : "r06/f36",
        "north" : "r06/f37",
        "west" : "r05/f36",
    ]));
    
}

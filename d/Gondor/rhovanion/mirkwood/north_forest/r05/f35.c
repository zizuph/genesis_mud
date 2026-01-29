#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r04/f36",
        "southwest" : "r05/f34",
        "south" : "r04/f35",
        "northwest" : "r06/f34",
        "east" : "r05/f36",
        "north" : "r06/f35",
        "northeast" : "r06/f36",
        "west" : "r05/f34",
    ]));
    
}

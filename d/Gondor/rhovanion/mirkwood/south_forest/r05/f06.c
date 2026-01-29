#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r06/f07",
        "south" : "r06/f06",
        "east" : "r05/f07",
        "north" : "r04/f06",
        "northeast" : "r04/f07",
    ]));
    
}

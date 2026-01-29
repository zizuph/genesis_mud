#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : "r22/f44",
        "south" : "r22/f45",
        "northwest" : "r20/f44",
        "east" : "r21/f46",
        "north" : "r20/f45",
        "northeast" : "r20/f46",
        "west" : "r21/f44",
    ]));
    
}

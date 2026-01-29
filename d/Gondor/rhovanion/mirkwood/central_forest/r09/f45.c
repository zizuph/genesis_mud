#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r08/f46",
        "southwest" : "r08/f44",
        "south" : "r08/f45",
        "northwest" : "r10/f44",
        "east" : "r09/f46",
        "north" : "r10/f45",
        "west" : "r09/f44",
    ]));
    
}

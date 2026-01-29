#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r09/f45",
        "southwest" : "r09/f43",
        "south" : "r09/f44",
        "east" : "r10/f45",
        "west" : "r10/f43",
    ]));
    
}

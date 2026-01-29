#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r15/f06",
        "northwest" : "r17/f04",
        "east" : "r16/f06",
        "north" : "r17/f05",
        "northeast" : "r17/f06",
        "west" : "r16/f04",
        "south" : VALE_DIR + "valen16w2",
        "southwest" : VALE_DIR + "valen16w3",
    ]));
    
}

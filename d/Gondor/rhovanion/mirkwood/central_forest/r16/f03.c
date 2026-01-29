#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "northwest" : "r17/f02",
        "east" : "r16/f04",
        "north" : "r17/f03",
        "northeast" : "r17/f04",
        "west" : VALE_DIR + "valen17w5",
        "south" : VALE_DIR + "valen16w4",
        "southwest" : VALE_DIR + "valen16w5",
        "southeast" : VALE_DIR + "valen16w3",
    ]));
    
}

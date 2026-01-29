#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "northwest" : "r16/f05",
        "east" : "r15/f07",
        "north" : "r16/f06",
        "northeast" : "r16/f07",
        "southeast" : VALE_DIR + "valen15w0",
        "south" : VALE_DIR + "valen15w1",
        "southwest" : VALE_DIR + "valen15w2",
        "west" : VALE_DIR + "valen16w2",
    ]));
    
}

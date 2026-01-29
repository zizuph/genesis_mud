#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r01",
        "south" : MIRKWOOD_OLDROAD_DIR + "r02",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r03",

        "west" : VALE_DIR + "valen1w1",
        "northwest" : VALE_DIR + "valen2w1",

        "east" : "r00/f08",
        "north" : "r01/f07",
        "northeast" : "r01/f08",
    ]));
    
}

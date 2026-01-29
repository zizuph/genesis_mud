#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r05/f11",
        "west" : "/d/Gondor/rhovanion/mirkwood/woodsmen/weanting1",
        "southwest" : "r05/p09-r05",
        "south" : "r05/f10",
        "northwest" : "r03/f09",
        "east" : "r04/f11",
        "north" : "r03/f10",
        "northeast" : "r03/f11",
    ]));
    
}

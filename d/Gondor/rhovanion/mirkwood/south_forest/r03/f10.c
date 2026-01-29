#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r04/f11",
        "south" : "r04/f10",
        "southwest" : "/d/Gondor/rhovanion/mirkwood/woodsmen/weanting1",
        "northwest" : "r02/f09",
        "east" : "r03/f11",
        "north" : "r02/f10",
        "northeast" : "r02/f11",
        "west" : "r03/f09",
    ]));
    
}

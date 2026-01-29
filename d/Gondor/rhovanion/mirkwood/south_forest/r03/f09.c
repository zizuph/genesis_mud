#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r04/f10",
        "south" : "/d/Gondor/rhovanion/mirkwood/woodsmen/weanting1",
        "southwest" : "r04/f08",
        "northwest" : "r02/p08-r02",
        "east" : "r03/f10",
        "north" : "r02/f09",
        "northeast" : "r02/f10",
        "west" : "r03/p08-r03",
    ]));
    
}

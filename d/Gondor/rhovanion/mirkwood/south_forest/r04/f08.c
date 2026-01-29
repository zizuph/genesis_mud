#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r05/p09-r05",
        "east" : "/d/Gondor/rhovanion/mirkwood/woodsmen/weanting1",
        "southwest" : "r05/f07",
        "south" : "r05/f08",
        "northwest" : "r03/f07",
        "north" : "r03/p08-r03",
        "northeast" : "r03/f09",
        "west" : "r04/f07",
    ]));
    
}

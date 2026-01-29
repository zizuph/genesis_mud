#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r06/p09-r06",
        "northeast" : "/d/Gondor/rhovanion/mirkwood/woodsmen/weanting1",
        "southwest" : "r06/f07",
        "south" : "r06/f08",
        "northwest" : "r04/f07",
        "east" : "r05/p09-r05",
        "north" : "r04/f08",
        "west" : "r05/f07",
    ]));
    
}

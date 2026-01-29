#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r12/f09",
        "southwest" : "r12/f07",
        "south" : "r12/f08",
        "east" : "/d/Gondor/rhovanion/mirkwood/woodsmen/gairent1",
        "northwest" : "r10/f07",
        "north" : "r10/p08-r10",
        "northeast" : "r10/f09",
        "west" : "r11/f07",
    ]));
    
}

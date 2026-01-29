#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r11/f10",
        "south" : "/d/Gondor/rhovanion/mirkwood/woodsmen/gairent1",
        "southwest" : "r11/f08",
        "northwest" : "r09/p08-r09",
        "east" : "r10/f10",
        "north" : "r09/f09",
        "northeast" : "r09/f10",
        "west" : "r10/p08-r10",
    ]));
    
}

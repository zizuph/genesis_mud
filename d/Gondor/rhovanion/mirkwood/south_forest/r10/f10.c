#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : "/d/Gondor/rhovanion/mirkwood/woodsmen/gairent1",
        "southeast" : "r11/f11",
        "south" : "r11/f10",
        "northwest" : "r09/f09",
        "east" : "r10/f11",
        "north" : "r09/f10",
        "northeast" : "r09/f11",
        "west" : "r10/f09",
    ]));
    
}

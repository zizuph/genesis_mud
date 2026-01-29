#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southeast" : "r03/f44",
        "southwest" : "r03/f42",
        "south" : "r03/f43",
        "east" : "/d/Gondor/rhovanion/mirkwood/goblins/hargnak1",
        "northwest" : "r01/f42",
        "north" : "r01/p43",
        "northeast" : "r01/f44",
        "west" : "r02/f42",
    ]));
    
}

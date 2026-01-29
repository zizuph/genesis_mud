#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f44",
        "southwest" : "r04/f42",
        "south" : "r04/f43",
        "northwest" : "r02/f42",
        "east" : "r03/f44",
        "northeast" : "/d/Gondor/rhovanion/mirkwood/goblins/hargnak1",
        "north" : "r02/f43",
        "west" : "r03/f42",
    ]));
    
}

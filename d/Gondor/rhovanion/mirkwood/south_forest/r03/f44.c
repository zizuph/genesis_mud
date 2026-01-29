#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southeast" : "r04/f45",
        "southwest" : "r04/f43",
        "south" : "r04/f44",
        "northwest" : "r02/f43",
        "east" : "r03/f45",
        "north" : "/d/Gondor/rhovanion/mirkwood/goblins/hargnak1",
        "northeast" : "r02/f45",
        "west" : "r03/f43",
    ]));
    
}

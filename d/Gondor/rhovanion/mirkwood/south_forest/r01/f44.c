#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southeast" : "r02/f45",
        "south" : "/d/Gondor/rhovanion/mirkwood/goblins/hargnak1",
        "southwest" : "r02/f43",
        "northwest" : "r00/f43",
        "east" : "r01/f45",
        "north" : "r00/f44",
        "northeast" : "r00/f45",
        "west" : "r01/p43",
    ]));
    
}

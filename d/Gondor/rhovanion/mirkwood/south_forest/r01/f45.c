#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f46",
        "south" : "r02/f45",
        "southwest" : "/d/Gondor/rhovanion/mirkwood/goblins/hargnak1",
        "northwest" : "r00/f44",
        "east" : "r01/f46",
        "north" : "r00/f45",
        "northeast" : "r00/f46",
        "west" : "r01/f44",
    ]));
    
}

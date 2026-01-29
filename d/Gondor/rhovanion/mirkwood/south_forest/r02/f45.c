#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southeast" : "r03/f46",
        "southwest" : "r03/f44",
        "south" : "r03/f45",
        "northwest" : "r01/f44",
        "east" : "r02/f46",
        "north" : "r01/f45",
        "northeast" : "r01/f46",
        "west" : "/d/Gondor/rhovanion/mirkwood/goblins/hargnak1",
    ]));
    
}

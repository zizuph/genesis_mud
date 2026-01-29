#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_OLDROAD_DIR + "r30",
        "north" : MIRKWOOD_OLDROAD_DIR + "r31",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r32",

        "southeast" : "r01/f37",
        "southwest" : "r01/f35",
        "south" : "r01/f36",
        "east" : "r00/f37",
        "west" : "r00/f35",
    ]));
    
}

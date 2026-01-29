#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_OLDROAD_DIR + "r39",
        "north" : MIRKWOOD_OLDROAD_DIR + "r40",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r41",

        "southeast" : "r01/f46",
        "southwest" : "r01/f44",
        "south" : "r01/f45",
        "east" : "r00/f46",
        "west" : "r00/f44",
    ]));
    
}

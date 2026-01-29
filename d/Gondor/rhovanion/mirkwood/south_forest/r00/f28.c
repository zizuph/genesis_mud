#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_OLDROAD_DIR + "r22",
        "north" : MIRKWOOD_OLDROAD_DIR + "r23",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r24",

        "southeast" : "r01/f29",
        "southwest" : "r01/f27",
        "south" : "r01/f28",
        "east" : "r00/f29",
        "west" : "r00/f27",
    ]));
    
}

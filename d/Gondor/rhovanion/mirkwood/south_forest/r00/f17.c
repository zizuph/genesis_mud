#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_OLDROAD_DIR + "r11",
        "north" : MIRKWOOD_OLDROAD_DIR + "r12",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r13",

        "southeast" : "r01/f18",
        "southwest" : "r01/f16",
        "south" : "r01/f17",
        "east" : "r00/f18",
        "west" : "r00/f16",
    ]));
    
}

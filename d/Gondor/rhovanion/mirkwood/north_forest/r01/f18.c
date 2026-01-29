#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(27);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_ELFPATH_DIR + "p17",

        "southeast" : "r00/f19",
        "south" : "r00/f18",
        "northwest" : "r02/f17",
        "east" : "r01/f19",
        "north" : "r02/f18",
        "northeast" : "r02/f19",
        "west" : "r01/f17",
    ]));
    
}

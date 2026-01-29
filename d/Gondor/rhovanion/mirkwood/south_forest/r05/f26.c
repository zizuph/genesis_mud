#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f27",
        "southwest" : "r06/f25",
        "south" : "r06/f26",
        "northwest" : "r04/f25",
        "east" : "r05/f27",
        "north" : "r04/f26",
        "northeast" : "r04/f27",
        "west" : "r05/f25",
    ]));
    
}

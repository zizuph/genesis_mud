#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f31",
        "southwest" : "r06/f29",
        "south" : "r06/f30",
        "northwest" : "r04/f29",
        "east" : "r05/f31",
        "north" : "r04/f30",
        "northeast" : "r04/f31",
        "west" : "r05/f29",
    ]));
    
}

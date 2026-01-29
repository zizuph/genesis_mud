#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f41",
        "southwest" : "r06/f39",
        "south" : "r06/f40",
        "northwest" : "r04/f39",
        "east" : "r05/f41",
        "north" : "r04/f40",
        "northeast" : "r04/f41",
        "west" : "r05/f39",
    ]));
    
}

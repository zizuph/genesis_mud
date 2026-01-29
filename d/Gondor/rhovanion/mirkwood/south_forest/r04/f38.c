#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(41);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f39",
        "southwest" : "r05/f37",
        "south" : "r05/f38",
        "northwest" : "r03/f37",
        "east" : "r04/f39",
        "north" : "r03/f38",
        "northeast" : "r03/f39",
        "west" : "r04/f37",
    ]));
    
}

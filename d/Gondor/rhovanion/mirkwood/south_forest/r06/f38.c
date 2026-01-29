#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(81);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f39",
        "southwest" : "r07/f37",
        "south" : "r07/f38",
        "northwest" : "r05/f37",
        "east" : "r06/f39",
        "north" : "r05/f38",
        "northeast" : "r05/f39",
        "west" : "r06/f37",
    ]));
    
}

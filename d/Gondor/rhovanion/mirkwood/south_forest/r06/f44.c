#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r07/f45",
        "southwest" : "r07/f43",
        "south" : "r07/f44",
        "northwest" : "r05/f43",
        "east" : "r06/f45",
        "north" : "r05/f44",
        "northeast" : "r05/f45",
        "west" : "r06/f43",
    ]));
    
}

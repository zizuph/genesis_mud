#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(80);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f37",
        "southwest" : "r07/f35",
        "south" : "r07/f36",
        "northwest" : "r05/f35",
        "east" : "r06/f37",
        "north" : "r05/f36",
        "northeast" : "r05/f37",
        "west" : "r06/f35",
    ]));
    
}

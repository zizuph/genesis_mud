#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(48);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f37",
        "southwest" : "r05/f35",
        "south" : "r05/f36",
        "northwest" : "r03/f35",
        "east" : "r04/f37",
        "north" : "r03/f36",
        "northeast" : "r03/f37",
        "west" : "r04/f35",
    ]));
    
}

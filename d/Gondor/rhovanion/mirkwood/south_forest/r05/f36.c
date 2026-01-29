#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(68);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f37",
        "southwest" : "r06/f35",
        "south" : "r06/f36",
        "northwest" : "r04/f35",
        "east" : "r05/f37",
        "north" : "r04/f36",
        "northeast" : "r04/f37",
        "west" : "r05/f35",
    ]));
    
}

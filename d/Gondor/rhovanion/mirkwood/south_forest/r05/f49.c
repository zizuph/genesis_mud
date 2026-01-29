#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r06/f50",
        "southwest" : "r06/f48",
        "south" : "r06/f49",
        "northwest" : "r04/f48",
        "east" : "r05/f50",
        "north" : "r04/f49",
        "northeast" : "r04/f50",
        "west" : "r05/f48",
    ]));
    
}

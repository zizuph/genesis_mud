#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f12",
        "southwest" : "r06/f10",
        "south" : "r06/f11",
        "northwest" : "r04/f10",
        "east" : "r05/f12",
        "north" : "r04/f11",
        "northeast" : "r04/f12",
        "west" : "r05/f10",
    ]));
    
}

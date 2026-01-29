#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(42);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r04/f24",
        "southwest" : "r04/f22",
        "south" : "r04/f23",
        "northwest" : "r06/f22",
        "east" : "r05/f24",
        "north" : "r06/f23",
        "northeast" : "r06/f23",
        "west" : "r05/f22",
    ]));
    
}

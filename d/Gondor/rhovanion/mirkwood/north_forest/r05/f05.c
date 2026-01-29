#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r04/f06",
        "southwest" : "r04/f04",
        "south" : "r04/f05",
        "northwest" : "r06/f04",
        "east" : "r05/f06",
        "north" : "r06/f05",
        "northeast" : "r06/f06",
        "west" : "r05/f04",
    ]));
    
}

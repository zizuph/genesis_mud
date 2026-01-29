#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r03/f06",
        "southwest" : "r03/f04",
        "south" : "r03/f05",
        "northwest" : "r05/f04",
        "east" : "r04/f06",
        "north" : "r05/f05",
        "northeast" : "r05/f06",
        "west" : "r04/f04",
    ]));
    
}

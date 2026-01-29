#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r03/f07",
        "southwest" : "r03/f05",
        "south" : "r03/f06",
        "northwest" : "r05/f05",
        "east" : "r04/f07",
        "north" : "r05/f06",
        "northeast" : "r05/f07",
        "west" : "r04/f05",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(37);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r03/f24",
        "southwest" : "r02/f22",
        "south" : "r02/f23",
        "northwest" : "r04/f22",
        "east" : "r03/f24",
        "north" : "r04/f23",
        "northeast" : "r04/f24",
        "west" : "r03/f22",
    ]));
    
}

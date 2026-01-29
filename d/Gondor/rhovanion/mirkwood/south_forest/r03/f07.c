#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r04/f08",
        "southwest" : "r04/f06",
        "south" : "r04/f07",
        "northwest" : "r02/f06",
        "east" : "r03/p08-r03",
        "north" : "r02/f07",
        "northeast" : "r02/p08-r02",
        "west" : "r03/f06",
    ]));
    
}
